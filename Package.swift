// swift-tools-version: 5.7
import PackageDescription

let version = "4.70.4"
let frameworks = [
    "iZettleSDK": "00dbfd95883107c8ec5624012cc4dcc63092be8d4f8d328cc885ac8677e5f151",
    "iZettlePayments": "b5944f0981c450099d8b379ee51eb6db3ee7cfd5be3f938e4895ee6d5bfaf815",
    "PPRiskMagnes": "7a83ff4134f686d8e048f6aa2bcaba05faeedb2d4341432a66b50b9e84fad041"
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
