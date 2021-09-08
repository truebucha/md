### Script

```
import Foundation

// MARK: - Model
class LocalizableStringModel {
    let key: String
    let localizableStrings: [String: String]

    init?(validArray: [String]) {
        guard validArray.count == languageLocales.count else { return nil }
        for str in validArray {
            guard !str.isEmpty else { return nil }
        }

        var validArrayWithoutKey = validArray
        validArrayWithoutKey.removeFirst()
        var languageFolders = languageLocales
        languageFolders.removeFirst()
        var dictinary = [String: String]()

        for (index, key) in languageFolders.enumerated() {
            let value = LocalizableStringModel.replaceDoubleQuotes(validArrayWithoutKey[index])
            dictinary[key] = value
        }

        self.key = validArray[0]
        self.localizableStrings = dictinary
    }

    convenience init?(array: [String]) {
        var haveNotCommas = true
        for str in array {
            if str.first == "\"" || str.last == "\"" {
                haveNotCommas = false
                break
            }
        }

        if array.count <= languageLocales.count, haveNotCommas {
            self.init(validArray: array)
        } else {
            var array = array
            var validArray = [String]()
            let key = array.remove(at: 0)
            var value = ""

            for str in array {
                var str = str
                if str.first != "\"", str.last != "\"", value.isEmpty {
                    validArray.append(str)
                    continue
                } else if str.first != "\"", str.last != "\"", !value.isEmpty {
                    value += str + ","
                }

                if str.first == "\"" {
                    str.removeFirst()
                    value += str + ","
                    continue
                }

                if str.last == "\"" {
                    str.removeLast()
                    value += str
                    validArray.append(value)
                    value = ""
                }
            }

            validArray.insert(key, at: 0)
            self.init(validArray: validArray)
        }
    }

    static func replaceDoubleQuotes(_ string: String) -> String {
        let newString = string.replacingOccurrences(
            of: "\"\"", with: "\\\"", options: .literal, range: nil)

        return  newString
    }
}

// MARK: - Properties
let fileName = "TruU-Localization.xlsx - iOS Mobile Localizable.csv"
var languageLocales = [String]()

// MARK: - Errors
enum ScriptError: Error {
    case missedLocalizationSource(file: URL)
    case emptySCVFile
    case cantGetPathToDownloadsDirectory
}

// MARK: - Methods
func readCSV(inputFile: String) throws -> [LocalizableStringModel] {
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
        let savedData = try String(contentsOf: inputFile)
        stringArray = savedData.components(separatedBy: "\n")
    } catch {
        Swift.debugPrint("\nError: \(error) \n")
        throw ScriptError.missedLocalizationSource(file: inputFile)
    }

    guard var columnHeadersLine = stringArray.first else {
        throw ScriptError.emptySCVFile }

    columnHeadersLine.removeLast()
    let arrayFirstStr = columnHeadersLine.components(separatedBy: ",")
    languageLocales = arrayFirstStr

    stringArray.removeSubrange(0...1)
    stringArray.forEach {
        var array = Array($0)
        array.removeLast()
        clearStringsArray.append(String(array))
    }

    for (index, str) in clearStringsArray.enumerated() {
        let array = str.components(separatedBy: ",")
        guard let model = LocalizableStringModel(array: array) else {
            let arrayWithoutKey = array[1...]
            var isOneOfLocolizableStringsNotEmpty = false
            arrayWithoutKey.forEach {
                if !$0.isEmpty { isOneOfLocolizableStringsNotEmpty = true }
            }

            if !array[0].isEmpty, isOneOfLocolizableStringsNotEmpty {
                Swift.debugPrint("Warning! Localization for key \(array[0]) == nil. String number \(index + 3)")
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
        modelsArray = try readCSV(inputFile: fileName)
    } catch {
        print("\n \(error) \n")
        return
    }

    let localizableStrings = createLocalizableFiles(with: modelsArray)
    writeToFiles(localizableStrings: localizableStrings)
}

main()
```

