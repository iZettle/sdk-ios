//
//  ManualCardEntryViewController.swift
//  iZettle SDK Sample
//
//  Created by Priyal Porwal on 22/06/23.
//  Copyright © 2023 iZettle. All rights reserved.
//

import UIKit
import iZettleSDK

class ManualCardEntryViewController: UIViewController {
    
    @IBOutlet weak var amountLabel: UILabel!
    @IBOutlet weak var stepper: UIStepper!
    
    var lastError: Error?
    var lastPayment: IZSDKManualCardEntryPaymentInfo?
    
    var currentAmount: Double = 10.0 {
        didSet {
            amountLabel.text = String(currentAmount)
        }
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        amountLabel.text = String(currentAmount)
        stepper.value = currentAmount
    }
    
    
    @IBAction func charge(_ sender: Any) {
        let uuid = UUID()
        let amount = NSDecimalNumber(string: amountLabel.text)
        
        iZettleSDK
            .shared()
            .chargeManualCardEntry(amount: amount,
                                   reference: uuid,
                                   presentFrom: self) { info, error in
                self.lastError = error
                self.lastPayment = info
                self.showConsole()
            }
    }
    
    @IBAction func retrieveLastPayment(_ sender: Any) {
        if let lastPayment = lastPayment {
            retrieve(uuid: UUID(uuidString: lastPayment.referenceNumber)!)
        } else {
            showAlert(title: "No payments to retrieve",
                      message: "Perform a successful payment to initiate a retrieve")
        }
    }
    
    @IBAction func refundLastPayment(_ sender: Any) {
        if let lastPayment = lastPayment {
            let reference = UUID(uuidString: lastPayment.referenceNumber)!
            refund(amount: lastPayment.amount, reference: reference)
        } else {
            showAlert(title: "No payments to refund",
                      message: "Perform a successful payment to initiate a refund")
        }
    }
    
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        if segue.identifier == "showConsole",
           let _ = sender as? ManualCardEntryViewController,
           let consoleVC = segue.destination as? ConsoleViewController {
            if let lastError = lastError {
                consoleVC.add(toLog: lastError)
            } else {
                consoleVC.add(toLog: lastPayment)
            }
        }
    }
}

private extension ManualCardEntryViewController {
    func retrieve(uuid: UUID) {
        iZettleSDK
            .shared()
            .retrieveManualCardEntryInfo(for: uuid,
                                         presentFrom: self) { paymentInfo, error in
                self.lastError = error
                self.lastPayment = paymentInfo
                self.showConsole()
            }
    }
    
    func refund(amount: NSDecimalNumber, reference: UUID) {
        let uuid = UUID()
        iZettleSDK
            .shared()
            .refundManualCardEntry(amount: amount,
                                   ofPayment: reference,
                                   withRefundReference: uuid,
                                   presentFrom: self) { paymentInfo, error in
                self.lastError = error
                self.lastPayment = paymentInfo
                self.showConsole()
            }
    }
    
    func showAlert(title: String, message: String) {
        let alert = UIAlertController(title: title, message: message, preferredStyle: .alert)
        let ok = UIAlertAction(title: "Ok", style: .default, handler: nil)
        alert.addAction(ok)
        present(alert, animated: true, completion: nil)
    }
    
    func showConsole() {
        performSegue(withIdentifier: "showConsole", sender: self)
    }
}
