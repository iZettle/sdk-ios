//
//  SelectionTableViewController.swift
//  iZettle SDK Sample
//
//  Copyright © 2022 PayPal Inc. All rights reserved.
//

import UIKit
import iZettleSDK

class SelectionTableViewController: UITableViewController {

    override func viewDidLoad() {
        super.viewDidLoad()
    }

    // MARK: - Table view data source

    override func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return 6
    }
    
    override func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let cell = tableView.dequeueReusableCell(withIdentifier: "listCell", for: indexPath)
        cell.detailTextLabel?.text = nil
        switch indexPath.row {
        case 0:
            cell.textLabel?.text = "Card Payment"
        case 1:
            cell.textLabel?.text = "PayPal QRC Payment"
        case 2:
            cell.textLabel?.text = "Venmo QRC Payment (US only)"
        case 3:
            cell.textLabel?.text = "Manual Card Entry Payment"
        case 4:
            cell.textLabel?.text = "Enforce account"
            cell.detailTextLabel?.text = AccountManager.shared().enforcedUserAccount
        case 5:
            cell.textLabel?.text = "Settings"
        default: break
        }
        return cell
    }
    
    // MARK: - Table view delegate
    
    override func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
        switch indexPath.row {
        case 0:
            let vc = storyboard!.instantiateViewController(withIdentifier: "cardPaymentViewController")
            navigationController?.pushViewController(vc, animated: true)
        case 1:
            let vc = storyboard!.instantiateViewController(withIdentifier: "qrcViewController")
            navigationController?.pushViewController(vc, animated: true)
        case 2:
            if #available(iOS 13, *) {
                let vc = storyboard!.instantiateViewController(withIdentifier: "qrcViewController") as! QRCPaymentViewController
                vc.paymentType = .venmo
                navigationController?.pushViewController(vc, animated: true)
            }
        case 3:
            let vc = storyboard!.instantiateViewController(withIdentifier: "manualCardEntryViewController") as! ManualCardEntryViewController
            navigationController?.pushViewController(vc, animated: true)
        case 4:
            enforceAccount()
        case 5:
            iZettleSDK.shared().presentSettings(from: self)
        default: break
        }
        
    }
    
    func enforceAccount() {
        let alert = UIAlertController.init(title: "Enforce user account", message: "Enter email", preferredStyle: .alert)
        let enforce = UIAlertAction(title: "Enforce", style: .default) { action in
            let email = alert.textFields?.first?.text
            AccountManager.shared().enforcedUserAccount = email
            self.tableView.reloadData()
        }
        
        let cancel = UIAlertAction(title: "Cancel", style: .cancel, handler: nil)
        alert.addAction(enforce)
        alert.addAction(cancel)
        alert.addTextField { textField in
            textField.text = AccountManager.shared().enforcedUserAccount
            textField.placeholder = "Enter email"
            textField.keyboardType = .emailAddress
            textField.clearButtonMode = .whileEditing
        }
        present(alert, animated: true, completion: nil)
    }
}
