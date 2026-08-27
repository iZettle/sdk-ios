// swift-tools-version: 5.7
import PackageDescription

let version = "4.70.4"
let frameworks = [
    "iZettleSDK": "3dbeb9d230973e82508072da8650e5e777322a75d1461bf317ab3864471e7b2e",
    "iZettlePayments": "47ef33a2fe781895c3492f980732500e6c43cbebf7099b487e280184e24f8311",
    "PPRiskMagnes": "f3d63ca13f921e1f51c4a407684162316293a127ac25364ee1eb07a2487f8f65"
]

let package = Package(
    name: "sdk-ios",
    platforms: [
        .iOS(.v12)
    ],
    products: [
        .library(
            name: "sdk-ios",
            targets: frameworks.map({ (name: String, checksum: String) in name }))
    ],
    dependencies: [],
    targets: frameworks.map({ (name: String, checksum: String) in Target.binaryTarget(
        name: name,
        url: "https://github.com/iZettle/sdk-ios/releases/download/\(version)/\(name).xcframework.zip",
        checksum: checksum) })
)
