Pod::Spec.new do |s|
  s.name         = 'iZettleSDK'
  s.version      = '2.3.2'
  s.summary      = 'iZettle SDK for iOS'
  s.description  = <<-DESC
                    For detailed information, please see iZettleSDK documentation and Readme.
                   DESC
  s.homepage     = 'https://www.izettle.com/'
  s.license      = { :type => 'Commercial', :file => 'LICENSE' }
  s.author       = { 'iZettle AB' => 'hello@izettle.com' }
  s.platform     = :ios, '9.0'
  s.source       = { :git => 'https://github.com/iZettle/sdk-ios.git', :tag => "#{s.version}" }
  s.source_files =  "#{s.name}/**/*.{h,swift}" 
  s.preserve_paths = 'iZettleSDK/iZettleSDK.xcframework'
  s.public_header_files = 'iZettleSDK/iZettleSDK.xcframework/**/*.h'
  s.vendored_frameworks = 'iZettleSDK/iZettleSDK.xcframework', 'iZettleSDK/iZettleShared.xcframework', 'iZettleSDK/iZettlePayments.xcframework', 'iZettleSDK/iZettleTransport.xcframework'
  s.frameworks = 'SystemConfiguration', 'CoreLocation', 'ExternalAccessory', 'AudioToolbox', 'AVFoundation', 'MediaPlayer', 'QuartzCore', 'Accelerate', 'MessageUI', 'CoreData'
  s.library   = 'z', 'c++'
  s.xcconfig  =  { 'OTHER_LDFLAGS' => '-ObjC', 'LIBRARY_SEARCH_PATHS' => '"$(PODS_ROOT)/iZettleSDK"' }
end
