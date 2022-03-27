```
import Foundation

// MARK: - Model
class LocalizableStringModel {
    let key: String
    let localizableStrings: [String: String]

    init?(lineArray: [String]) {
        guard lineArray.count == languageLocales.count else {
            print("We have \(languageLocales.count) in key + locales but found \(lineArray.count) elements in line")
            return nil
        }
        for str in lineArray {
            guard !str.isEmpty else { return nil }
        }

        var validArrayWithoutKey = lineArray
        validArrayWithoutKey.removeFirst()
        var languageFolders = languageLocales
        languageFolders.removeFirst()
        var dictinary = [String: String]()

        for (index, key) in languageFolders.enumerated() {
            dictinary[key] = validArrayWithoutKey[index].replacingOccurrences(of: "\"", with: "\\\"")
        }

        self.key = lineArray[0]
        self.localizableStrings = dictinary
    }
}

// MARK: - Properties
let fileName = "TruU-Localization.xlsx - iOS Mobile Localizable.tsv"
var languageLocales = [String]()

// MARK: - Errors
enum ScriptError: Error {
    case missedLocalizationSource(file: URL)
    case emptySCVFile
    case cantGetPathToDownloadsDirectory
}

// MARK: - Methods
func readTSV(inputFile: String) throws -> [LocalizableStringModel] {
    var stringArray = [String]()
    var clearStringsArray = [String]()
    var modelsArray = [LocalizableStringModel]()

    guard let fileUrl = try? FileManager.default.url(
            for: .downloadsDirectory,
            in: .userDomainMask,
            appropriateFor: nil,
            create: false) else {
        throw ScriptError.cantGetPathToDownloadsDirectory
    }

    let inputFile = fileUrl
        .appendingPathComponent(inputFile)

    do {
        let csv = try String(contentsOf: inputFile)
        // We replace C string format specifier with string one "%1$s" -> "%1$@"
        let scvIOSformat = csv.replacingOccurrences(
            of: "$s",
            with: "$@",
            options: .caseInsensitive
        )
        stringArray = scvIOSformat.components(separatedBy: "\n")
    } catch {
        Swift.debugPrint("\nError: \(error) \n")
        throw ScriptError.missedLocalizationSource(file: inputFile)
    }

    guard var columnHeadersLine = stringArray.first else {
        throw ScriptError.emptySCVFile }

    columnHeadersLine.removeLast()
    let arrayFirstStr = columnHeadersLine.components(separatedBy: "\t")
    languageLocales = arrayFirstStr

    stringArray.removeSubrange(0...1)
    stringArray.forEach {
        var array = Array($0)
        array.removeLast()
        clearStringsArray.append(String(array))
    }

    for (index, str) in clearStringsArray.enumerated() {
        let array = str.components(separatedBy: "\t")
        guard let model = LocalizableStringModel(lineArray: array) else {
            let arrayWithoutKey = array[1...]
            var isOneOfLocolizableStringsNotEmpty = false
            arrayWithoutKey.forEach {
                if !$0.isEmpty { isOneOfLocolizableStringsNotEmpty = true }
            }

            if !array[0].isEmpty, isOneOfLocolizableStringsNotEmpty {
                Swift.debugPrint("""
                    Line: \(index + 3), Missing localization for key \(array[0]): \
                    \(arrayWithoutKey.reduce(into: "", { $0 += "\($1);" }))
                    """
                )
            }
            continue
        }
        modelsArray.append(model)
    }

    return modelsArray
}

func createLocalizableFiles(with modelsArray: [LocalizableStringModel]) -> [String: String] {
    var languageFolders = languageLocales
    languageFolders.removeFirst()
    var localizableStrings = [String: String]()

    for folderName in languageFolders {
        var localizableString = ""
        for model in modelsArray {
            for (language, str) in model.localizableStrings {
                if language == folderName {
                    localizableString += "\n/*  */\n" + "\"" + model.key + "\"" + " = " + "\"" + str + "\"" + ";\n"
                }
            }
        }
        localizableStrings[folderName] = localizableString
    }
    return localizableStrings
}

func writeToFiles(localizableStrings: [String: String]) {
    for (locale, str) in localizableStrings {
        let pathToLocalizableFile = "TruU/TruU/Resources/\(locale).lproj/Localizable.strings"
        var url = URL(fileURLWithPath: FileManager.default.currentDirectoryPath)
        url.deleteLastPathComponent()
        url.appendPathComponent(pathToLocalizableFile)

        do {
            try str.write(to: url, atomically: false, encoding: .utf8)
            print("Success")
        } catch {
            print("Write error for locale \(locale): \(error.localizedDescription)")
        }
    }
}

func main() {
    let modelsArray: [LocalizableStringModel]
    do {
        modelsArray = try readTSV(inputFile: fileName)
    } catch {
        print("\n \(error) \n")
        return
    }

    let localizableStrings = createLocalizableFiles(with: modelsArray)
    writeToFiles(localizableStrings: localizableStrings)
}

main()
```