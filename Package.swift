// swift-tools-version: 5.7
import PackageDescription

let version = "4.83.0"
let frameworks = [
    "iZettleSDK": "b2f2e3790e97d22d6e2b35dab8ccacd0a4a4a8f54e7fcaca811f7711fb670f5f",
    "iZettlePayments": "fba4214750f3a64376b0338a95eace5dda6054c693681799803c4d90d9030e56",
    "PPRiskMagnes": "4a54e3b8a514d54e1d6810a8b9595be87e00b5459c1ef11a1c1adedfbd1a4703"
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
