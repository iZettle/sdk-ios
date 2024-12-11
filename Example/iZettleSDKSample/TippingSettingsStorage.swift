//
//  TippingSettingsStorage.swift
//  iZettle SDK Sample
//
//  Created by Mohanna Zakizadeh on 2024-10-31.
//  Copyright © 2024 iZettle. All rights reserved.
//


import Foundation

final class TippingSettingsStorage {

    private static let zettleReaderTippingKey = "com.izettle.iZorn.tipping_type_zettle"
    private static let paypalReaderTippingKey = "com.izettle.iZorn.tipping_type_paypal"
    private static let paypalReaderPredefinedTipsKey = "com.izettle.iZorn.predefined_tips_paypal"

    static let shared = TippingSettingsStorage()

    var zettleReaderTippingStyle: UInt {
        get {
            UserDefaults.standard.extract(type: UInt.self, fromKey: Self.zettleReaderTippingKey) ?? 0
        }
        set {
            UserDefaults.standard.set(newValue, for: Self.zettleReaderTippingKey)
        }
    }

    var paypalReaderTippingStyle: UInt {
        get {
            UserDefaults.standard.extract(type: UInt.self, fromKey: Self.paypalReaderTippingKey) ?? 0
        }
        set {
            UserDefaults.standard.set(newValue, for: Self.paypalReaderTippingKey)
        }
    }

    var paypalReaderPredefinedTips: [UInt]? {
        get {
            UserDefaults.standard.extract(type: [UInt].self, fromKey: Self.paypalReaderPredefinedTipsKey)
        }
        set {
            UserDefaults.standard.set(newValue, for: Self.paypalReaderPredefinedTipsKey)
        }
    }
}
