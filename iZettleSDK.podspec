Pod::Spec.new do |s|
  s.name         = 'iZettleSDK'
  s.version      = '4.70.3'
  s.summary      = 'iZettle SDK for iOS'
  s.description  = <<-DESC
                    For detailed information, please see iZettleSDK documentation and Readme.
                   DESC
  s.homepage     = 'https://www.zettle.com/'
  s.license      = { :type => 'Commercial', :file => 'LICENSE' }
  s.author       = { 'PayPal Inc' => 'hello@izettle.com' }
  s.platform     = :ios, '12.0'
  s.pod_target_xcconfig = { 'VALID_ARCHS' => 'arm64 armv7 x86_64' }
  s.source       = { :http => "https://github.com/iZettle/sdk-ios/releases/download/#{s.version}/iZettleSDK.zip", type: :zip, :sha256 => '396011091af85ed304c4a704859d5f3b131928a5d09db8baa9e378181e636302' }
  s.source_files = []
  s.preserve_paths = '**/*'
  s.public_header_files = 'iZettleSDK/iZettleSDK.xcframework/**/*.h'
  s.vendored_frameworks = [
    'iZettleSDK/iZettleSDK.xcframework', 
    'iZettleSDK/iZettlePayments.xcframework', 
    'iZettleSDK/PPRiskMagnes.xcframework'
  ]
  s.frameworks = 'SystemConfiguration', 'CoreLocation', 'ExternalAccessory', 'AudioToolbox', 'AVFoundation', 'MediaPlayer', 'QuartzCore', 'Accelerate', 'MessageUI', 'CoreData'
  s.library   = 'z', 'c++'
  s.xcconfig  =  { 'OTHER_LDFLAGS' => '-ObjC', 'LIBRARY_SEARCH_PATHS' => '"$(PODS_ROOT)/iZettleSDK"' }
end
