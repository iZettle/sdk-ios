// swift-tools-version: 5.7
import PackageDescription

let package = Package(
    name: "sdk-ios",
    platforms: [
        .iOS(.v12)
    ],
    products: [
        .library(
            name: "sdk-ios",
            targets: ["iZettleSDK", "iZettlePayments", "PPRiskMagnes"]),
    ],
    dependencies: [],
    targets: [
        .binaryTarget(
            name: "iZettleSDK",
            url: "https://github.com/iZettle/sdk-ios/releases/download/4.53.1/iZettleSDK.xcframework.zip",
            checksum: "8ee18a692066c71dddff9c56e88ca5713520e0d9bb6f59c4409d1e54ab42a274"),
        .binaryTarget(
            name: "iZettlePayments",
            url: "https://github.com/iZettle/sdk-ios/releases/download/4.53.1/iZettlePayments.xcframework.zip",
            checksum: "46783aa5cb0ceeca343c3560d974ea4e2d38a2db95f8bc83df30f2d86cefc392"),
        .binaryTarget(
            name: "PPRiskMagnes",
            url: "https://github.com/iZettle/sdk-ios/releases/download/4.53.1/PPRiskMagnes.xcframework.zip", // TODO: not available today
            checksum: "todo")
    ]
)
