// swift-tools-version: 5.7
import PackageDescription

let version = "4.70.3"
let frameworks = [
    "iZettleSDK": "f2c5c7be23a146d109a650194d955a60aefe91a0a5916d31253cf6c1ab96f940",
    "iZettlePayments": "a8bdcb4d2df0dbcfb8c1ab7d0fc1560747cffc828feca6170de2be0ad9eaeb87",
    "PPRiskMagnes": "fe927ec7be15083a698b955a430d0a0bb436d19c6483a49880bb1c9b15ba5652"
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
