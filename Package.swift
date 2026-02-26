// swift-tools-version: 5.7
import PackageDescription

let version = "UNSET"
let frameworks = [
    "iZettleSDK": "UNSET",
    "iZettlePayments": "UNSET",
    "PPRiskMagnes": "UNSET"
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
