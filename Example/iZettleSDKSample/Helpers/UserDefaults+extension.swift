//
//  UserDefaults+extension.swift
//  iZettle SDK Sample
//
//  Copyright © 2024 PayPal Inc. All rights reserved.
//


extension UserDefaults {
    func set<Object: Encodable>(_ objects: Array<Object>, for key: String) {
        set(try? JSONEncoder().encode(objects), forKey: key)
    }
    
    func set<Object: Encodable>(_ object: Object, for key: String) {
        set(try? JSONEncoder().encode(object), forKey: key)
    }

    func extract<Object: Decodable>(type: Object.Type, fromKey key: String) -> Object? {
        guard let data = value(forKey: key) as? Data else { return nil }
        return try? JSONDecoder().decode(type, from: data)
    }
}
