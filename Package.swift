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
            targets: ["iZettleSDK", "iZettlePayments"]),
    ],
    dependencies: [],
    targets: [
        .binaryTarget(
            name: "iZettleSDK", 
            path: "./iZettleSDK/iZettleSDK.xcframework"),
        .binaryTarget(
            name: "iZettlePayments", 
            path: "./iZettleSDK/iZettlePayments.xcframework")
    ]
)
