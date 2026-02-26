// swift-tools-version: 5.7
import PackageDescription

let version = "4.70.3"
let frameworks = [
    "iZettleSDK": "818fe69db3d0f3ffc067ba69675090ca239909406fb8b1cf2876aacb8fe98de2",
    "iZettlePayments": "4e28ddd0f0474b2a5651fd86b0d27e364d9303574522bd7c7c29514aa7ac9799",
    "PPRiskMagnes": "630b7cc093d357fa92fd9d7e4e5d297e4865d1fc345e4e74c5f47e81f2faf5fa"
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
