// swift-tools-version: 5.7
import PackageDescription

let version = "4.70.3"
let frameworks = [
    "iZettleSDK": "84a1d5aed9c333db716458e5900744eabdb99f63cc0ee44056acfe5d206e638a",
    "iZettlePayments": "5c4c7856e8d7093e43412db09e788c4194e5d5f0b4ae095788407250662a10b4",
    "PPRiskMagnes": "7734737a9c399fc93725099ab7e946cc32add965bbd69ab9d432bff4da7f8d0a"
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
