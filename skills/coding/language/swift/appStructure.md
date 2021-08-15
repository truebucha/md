
## Integration

it runs when app start and open all desired gates

this is a point of customization of app connection to the outside world


```swift

protocol IntegrationInterface {
    
    func enable(launchOptions: [AnyHashable : Any]?)
}

protocol IntegrationSubitemInterface {
    
    func enable(infoDictionary: [String : Any]?, launchOptions: [AnyHashable : Any]?)
}

class Integration: IntegrationInterface {
    
    let realm: IntegrationSubitemInterface = RealmIntegration()
    let analytics: IntegrationSubitemInterface = GoogleAnalyticsIntegration()
    let crashlytics: IntegrationSubitemInterface = CrashlyticsIntegration()
    let parse: IntegrationSubitemInterface = ParseIntegration()
    let geocoder: IntegrationSubitemInterface = GoogleGeocoderIntegration()
    let cloud: IntegrationSubitemInterface = CloudIntegration()
    
    func enable(launchOptions: [AnyHashable : Any]?) {
        
        let info = Bundle.main.infoDictionary
        
        crashlytics.enable(infoDictionary: info, launchOptions: launchOptions)
        realm.enable(infoDictionary: info, launchOptions: launchOptions)
        analytics.enable(infoDictionary: info, launchOptions: launchOptions)
        parse.enable(infoDictionary: info, launchOptions: launchOptions)
        geocoder.enable(infoDictionary: info, launchOptions: launchOptions)
        cloud.enable(infoDictionary: info, launchOptions: launchOptions)
    }
}

```

at some point integration of gate should get all needed values and open one or report that failed


```swift

import Foundation


class ParseIntegration: IntegrationSubitemInterface {
    
    func enable(infoDictionary: [String : Any]?,
                launchOptions: [AnyHashable : Any]?) {
        
        let parse = infoDictionary?["Parse"] as? NSDictionary
        let parseAppId = parse?["AppId"] as? String
        let parseClientKey = parse?["ClientKey"] as? String
        let parseServer = parse?["ServerUrl"] as? String
        guard let appId = parseAppId,
            let clientKey = parseClientKey,
            let server = parseServer else {
                
            print("[Error]: Retrive parse values from info dictionary failed: Parse-> AppId, ClientKey, ServerUrl")
            return
        }
        
        let succeed = ParseGate.shared.connect(
            appId: appId,
            clientKey: clientKey,
            server: server)
        guard succeed else {
            print("[Error] Parse integration failed")
            return
        }
        ParseGate.shared.trackAppOpened(launchOptions: launchOptions)
    }
}


```

## Gates 

Each gate represent a connection to the outside world

It could be a remote or system service, database, framework, accessory, connected device, user

This is example of a simple gate

```swift 

import Foundation
import Parse

class ParseGate {
    
    static let shared: ParseGate = ParseGate()
    
    var isOpen: Bool = false
    
    func open(appId: String,
                 clientKey: String,
                 server: String) -> Bool {
        guard !isOpen else {
            
            print("[Error]: Parse Gate already opened")
            return false
        }
        
        let configuration = ParseClientConfiguration { (configuration) in
            
            configuration.applicationId = appId
            configuration.clientKey = clientKey
            configuration.server = server
            configuration.isLocalDatastoreEnabled = true
        }
        
        Parse.initialize(with: configuration)
        print("[]: Parse Gate open succeed")
        isConnected = true
        return true
    }
    
    func trackAppOpened(launchOptions: [AnyHashable : Any]?) {
        PFAnalytics.trackAppOpened(launchOptions: launchOptions)
    }
}

```

this is an example of a more complex gate

```swift 


protocol SettingsGateProtocol {
    var sensorConnectedToRouter : Bool {get set}
    var calibrationStep: Float {get set}
    var sensorIp: String? {get}
    var userDefinedSensorIp : String? {get set}
    var sensorPort: Int {get set}
    var sensorPath: String? {get set}
    var dataRequestUrl: URL? {get}
    var coPpmDecimalPlaces: Int {get set}
    var analogZeroLevel: Double {get set}
    var requestIntervalInSec: Int {get set}
    var coPpmCoefficient: Float {get set}
}

protocol SettingsGateFactoryProtocol {
    func settingsGate() -> SettingsGateProtocol
}

// MARK: - settings -

class SettingsGate: SettingsGateProtocol {
    var dataRequestUrl: URL?
    
    // MARK: - property -
    
    static let shared: SettingsGate = SettingsGate()
    
    var sensorConnectedToRouter : Bool {
        get {
            let result = UserDefaults.standard.bool(forKey: Keys.sensorConnectedToRouter)
            return result
        }
        
        set {
            UserDefaults.standard.set(newValue, forKey: Keys.sensorConnectedToRouter)
        }
    }
    
    var calibrationStep : Float {
        get {
            let result = UserDefaults.standard.float(forKey: Keys.calibrationStep)
            guard result != 0 else {
                return Defaults.calibrationStep
            }
            return result
        }
        
        set {
            UserDefaults.standard.set(newValue, forKey: Keys.calibrationStep)
        }
    }
    
    var sensorIp: String? {
        get {
            if (sensorConnectedToRouter) {
                return userDefinedSensorIp
            }
            
            return ""
        }
    }
    
    var userDefinedSensorIp : String? {
        get {
            let result = UserDefaults.standard.object(forKey: Keys.sensorStationIp) as? String
            return result
        }
        
        set {
            UserDefaults.standard.set(newValue, forKey: Keys.sensorStationIp)
        }
    }
    
    var sensorPort : Int {
        get {
            let result = UserDefaults.standard.integer(forKey: Keys.sensorPort)
            guard result != 0
                else { return Defaults.sensorPort }
            
            return result
        }
        
        set {
            UserDefaults.standard.set(newValue, forKey: Keys.sensorPort)
        }
    }
    
    var sensorPath: String? {
        
        get {
            
            let result = UserDefaults.standard.object(forKey: Keys.sensorPath) as? String
            guard result != nil else {
                
                return Defaults.sensorPath
            }
            return result
        }
        set {
            
            UserDefaults.standard.set(newValue, forKey: Keys.sensorPath)
        }
    }
    
    var requestIntervalInSec : Int {
        get {
            guard UserDefaults.standard.dictionaryRepresentation().keys.contains(Keys.requestIntervalInSec)
                else { return Defaults.requestIntervalInSec }
            
            let result = UserDefaults.standard.integer(forKey: Keys.requestIntervalInSec)
            
            return result
        }
        
        set {
            UserDefaults.standard.set(newValue, forKey: Keys.requestIntervalInSec)
        }
    }
    
    var analogZeroLevel : Double {
        get {
            guard UserDefaults.standard.dictionaryRepresentation().keys.contains(Keys.analogZeroLevel)
                else { return Defaults.analogZeroLevel }
            let result = UserDefaults.standard.double(forKey: Keys.analogZeroLevel)
            
            return result
        }
        
        set {
            UserDefaults.standard.set(newValue, forKey: Keys.analogZeroLevel)
        }
    }
    
    var coPpmCoefficient : Float {
        get {
            guard UserDefaults.standard.dictionaryRepresentation().keys.contains(Keys.coPpmCoefficient)
                else { return Defaults.coPpmCoefficient }
            
            let result = UserDefaults.standard.float(forKey: Keys.coPpmCoefficient)
            return result
        }
        
        set {
            UserDefaults.standard.set(newValue, forKey: Keys.coPpmCoefficient)
        }
    }
    
    var coPpmDecimalPlaces : Int {
        get {
            guard UserDefaults.standard.dictionaryRepresentation().keys.contains(Keys.coPpmDecimalPlaces)
                else { return Defaults.coPpmDecimalPlaces }
            
            let result = UserDefaults.standard.integer(forKey: Keys.coPpmDecimalPlaces)
            
            return result
        }
        
        set {
            UserDefaults.standard.set(newValue, forKey: Keys.coPpmDecimalPlaces)
        }
    }
}

// MARK: - bundle keys -

fileprivate struct Keys {
    static let sensorConnectedToRouter = "Sensor Connected To Router: Bool"
    static let sensorStationIp = "Sensor Station Ip: String"
    static let sensorApIp = "Sensor Ap Ip:String"
    static let sensorPort = "Sensor Port: Int"
    static let sensorPath = "Sensor Path: String"
    static let requestIntervalInSec = "Request Interval In Sec: Int"
    static let analogZeroLevel = "Analog Zero Level: Int"
    static let coPpmCoefficient = "Co Ppm Coefficient: Float"
    static let coPpmDecimalPlaces = "Co Ppm Decimal Places: Int"
    static let calibrationStep = "Calibration Step: Float"
}

// MARK: - defaults -

fileprivate struct Defaults {
    static let sensorPort: Int = 80
    static let sensorPath: String = "/measure"
    static let sensorInApMode: Bool = true
    static let requestIntervalInSec: Int = 5
    static let analogZeroLevel: Double = 0.0
    static let coPpmCoefficient: Float = 1
    static let coPpmDecimalPlaces: Int = 1
    static let calibrationStep: Float = 2
}

```

## Interface Model

This item holds the view to interact with user and object models, which provide a data.

It handle user actions, generate system actions to models, gates, 
It process initial State and changeSets that object model provide.


In general - platform independed

```swift

//
//  Interface.swift
//  iotSensorClient
//
//  Created by Kanstantsin Bucha on 12/31/18.
//  Copyright � 2018 BuchaBros. All rights reserved.
//

import Foundation

// MARK: Interface common

protocol InterfaceEventsHandlerProtocol {
    func handleEvent()
}


enum SlotTransactionOptions {
    case noAnimation
    case animation
}

protocol InterfaceSlotsProviderProtocol {
    var interfaceSlots: [InterfaceSlotProtocol] {get}
    
    func mountAllSlots(with options: SlotTransactionOptions)
    func unmountAllSlots(with options: SlotTransactionOptions)
}

typealias InterfaceModelMountBlock = (_ plug: InterfaceModelProtocol,
                                    _ options: SlotTransactionOptions) -> Void
typealias InterfaceModelUnmountBlock = (_ options: SlotTransactionOptions) -> Void

// MARK: Simple interface

protocol InterfaceModelProtocol:
    InterfaceSlotsProviderProtocol {
   
    var interface: InterfaceRepresentation {get}
}

protocol InterfaceSlotProtocol {
    var hidden: Bool {get set}
    var currentPlug: InterfaceModelProtocol? {get}

    var mountIMBlock: InterfaceModelMountBlock {get}
    var unmountIMBlock:  InterfaceModelUnmountBlock {get}
}

// MARK: - Stack interface

protocol StackInterfaceSlotProtocol: InterfaceSlotProtocol {}

// MARK: - Tabs interface

protocol TabInterfaceModelProtocol: InterfaceModelProtocol {
    var enabled: Bool {get set}
    var tabItem: TabItemRepresentation {get}
}

protocol TabsInterfaceSlotProtocol: InterfaceSlotProtocol {
    var tabPlugs: [TabInterfaceModelProtocol] {get set}
}

// MARK: - Extesnsions

extension InterfaceModelProtocol {
    func mountAllSlots(with options: SlotTransactionOptions) {
    }
    
    func unmountAllSlots(with options: SlotTransactionOptions) {
        
    }
}


```

device specific 

```swift

typealias InterfaceRepresentation = UIViewController
typealias TabItemRepresentation = UITabBarItem

```

window manager

```swift 

import Foundation

protocol WindowManagerProtocol {
    
    func acceptMainSlot(_ slot: InterfaceSlotProtocol)
}

protocol WindowManagerFactoryProtocol {
    
    func windowManager() -> WindowManagerProtocol
}

typealias WindowManagerInjection = MainFactoryProtocol

class WindowManager: WindowManagerProtocol {
    
    private var mainSlot: InterfaceSlotProtocol?
    
    let injection: WindowManagerInjection
    
    init(inject injection: WindowManagerInjection) {
        self.injection = injection
    }
    
    func acceptMainSlot(_ slot: InterfaceSlotProtocol) {
        guard mainSlot == nil else {
            return
        }
        mainSlot = slot
        createInterface()
    }
    
    func createInterface() {
        guard let slot = mainSlot else {
            return
        }
        let interfaceModel = injection.viewsProvider().measurementVC()
        slot.mountIMBlock(interfaceModel, .noAnimation)
    }
}

```

iOS interface slot

```swift

import Foundation

class IosInterfaceSlot: InterfaceSlotProtocol {

    var hidden: Bool = false
    var currentPlug: InterfaceModelProtocol?
    
    let mountIMBlock: InterfaceModelMountBlock
    let unmountIMBlock:  InterfaceModelUnmountBlock
    
    init(mountIMBlock: @escaping InterfaceModelMountBlock,
         unmountIMBlock: @escaping InterfaceModelUnmountBlock) {
        self.mountIMBlock = mountIMBlock
        self.unmountIMBlock = unmountIMBlock
    }
}

```

app start 

```swift

func application(_ application: UIApplication,
                     didFinishLaunchingWithOptions launchOptions: [UIApplicationLaunchOptionsKey: Any]?) -> Bool {
        
        window = UIWindow()
        let mainSlot = IosInterfaceSlot(mountIMBlock: { (interfaceModel, _) in
            self.window?.rootViewController = interfaceModel.interface
        }) { (_) in
            self.window?.rootViewController = nil
        }
        Injector.shared.windowManager().acceptMainSlot(mainSlot)
        window?.makeKeyAndVisible()
        return true
    }
    
```

in general UIViewControllers could be a View and also a Interface Model

```swift

import UIKit
import Charts

fileprivate let maxDisplayableEntriesCount: Int = 15;

typealias MeasurementVCInjection =
    MeasurementModelFactoryProtocol &
    ViewsProviderFactoryProtocol

class MeasurementVC: UIViewController, InterfaceModelProtocol {
    
    @IBOutlet weak var chartView: BarChartView!
    @IBOutlet weak var startStopButton: UIButton!
    @IBOutlet weak var log: UITextView!
    @IBOutlet weak var coPpmValueLabel: UILabel!
    
    var interface: InterfaceRepresentation {
        get {
            return self
        }
    }
    var interfaceSlots: [InterfaceSlotProtocol] {
        get {
            return []
        }
    }

    private var injection: MeasurementVCInjection!
    private var model: MeasurementModelProtocol!
    
    static func view(with injection: MeasurementVCInjection) -> MeasurementVC {
        let result = injection.viewsProvider().loadView(of: "MeasurementVC") as! MeasurementVC
        result.injection = injection
        result.model = injection.measurementModel()
        return result
    }
    
    required init?(coder aDecoder: NSCoder) {
        super.init(coder: aDecoder)
    }
    
}
    
```

## Injector 

It is a factory for all object models, interface models, gates and more
It is handle dependencies tree of the app


```swift

import Foundation

typealias MainFactoryProtocol =
    ViewsProviderFactoryProtocol &
    // Models
    MeasurementModelFactoryProtocol &
    DropboxModelFactoryProtocol &
    // Gates
    StorageGateFactoryProtocol &
    SettingsGateFactoryProtocol &
    SensorGateFactoryProtocol &
    RouterGateFactoryProtocol &
    DropboxGateFactoryProtocol &
    AppWindowGateFactoryProtocol &
    WindowManagerFactoryProtocol

class Injector: MainFactoryProtocol {
    
    static let shared = Injector()
    
    // MARK: - WindowManagerFactoryProtocol
    
    func windowManager() -> WindowManagerProtocol {
        return WindowManager(inject: self)
    }

    // MARK: - ViewsProviderFactoryProtocol

    func viewsProvider() -> ViewsProviderProtocol {
        return ViewsProvider(inject: self)
    }
    
    // MARK: - Models -
    
    // MARK: MeasurementModelFactoryProtocol
    
    func measurementModel() -> MeasurementModelProtocol {
        return MeasurementModel(inject: self)
    }
    
    func dropboxModel() -> DropboxModelProtocol {
        return DropboxModel(inject: self)
    }
    
    // MARK: - Gates - 
    
    // MARK: SettingsGateFactoryProtocol
    
    func settingsGate() -> SettingsGateProtocol {
        return SettingsGate.shared
    }
    
    // MARK: StorageGateFactoryProtocol
    
    func storageGate() -> StorageGateProtocol {
        return StorageGate.shared
    }
    
    // MARK: SensorGateFactoryProtocol
    
    func sensorGate() -> SensorGateProtocol {
        return SensorGate.shared
    }
    
    // MARK: RouterGateFactoryProtocol
    
    func routerGate() -> RouterGateProtocol {
        return RouterGate.shared
    }
    
    // MARK: DropboxGateFactoryProtocol
    
    func dropboxGate() -> DropboxGateProtocol {
        return DropboxGate.shared
    }
    
    // MARK: AppWindowGateFactoryProtocol
    
    func appWindowGate() -> AppWindowGateProtocol {
        return AppWindowGate.shared
    }
}

```

