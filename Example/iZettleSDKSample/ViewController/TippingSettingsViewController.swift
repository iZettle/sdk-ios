//
//  TippingSettingsViewController.swift
//  iZettle SDK Sample
//
//  Copyright © 2024 PayPal Inc. All rights reserved.
//

import UIKit
import iZettleSDK

final class TippingSettingsViewController: UITableViewController {
    
    private struct InteractiveSection {
        let title: String?
        let rows: [InteractiveRow]
    }

    private struct InteractiveRow {
        let title: String
        let subtitle: String?
        let elementId: UInt
        let isSelected: Bool
        let action: (() -> Void)?
        
        init(tippingStyle: IZZettleReaderTippingStyle,
             selectedTippingId: UInt) {
            elementId = tippingStyle.rawValue
            title = tippingStyle.title
            self.isSelected = tippingStyle.rawValue == selectedTippingId
            action = nil
            subtitle = nil
        }

        init(tippingStyle: IZPayPalReaderTippingStyle,
             selectedTippingId: UInt) {
            elementId = tippingStyle.rawValue
            title = tippingStyle.title
            self.isSelected = tippingStyle.rawValue == selectedTippingId
            action = nil
            subtitle = nil
        }

        init(presetNumber: UInt,
             value: UInt?,
             action: @escaping () -> Void) {
            elementId = presetNumber
            title = "Option \(presetNumber)"
            if let value {
                subtitle = "\(value) %"
            } else {
                subtitle = "N/A"
            }
            self.action = action
            isSelected = false
        }

        init(title: String,
             action: @escaping () -> Void) {
            self.title = title
            self.action = action
            subtitle = nil
            isSelected = false
            elementId = 0
        }
    }

    private var dataSource: [InteractiveSection] = []

    private var closeButton: UIBarButtonItem {
        .init(
            title: "Close",
            style: .done,
            target: self,
            action: #selector(close)
        )
    }

    override func viewDidLoad() {
        super.viewDidLoad()
        title = "Tipping Settings"
        navigationItem.leftBarButtonItem = closeButton
        navigationItem.backBarButtonItem = UIBarButtonItem()
        tableView.showsVerticalScrollIndicator = false
        tableView.separatorStyle = .singleLine
        tableView.tableFooterView = UIView()
        dataSource = dataSourceWithSelectedOption()
    }

    @objc func close() {
        self.dismiss(animated: true)
    }

    private func dataSourceWithSelectedOption() -> [InteractiveSection] {
        let selectedZettleTipping = TippingSettingsStorage.shared.zettleReaderTippingStyle
        let selectedPayPalTipping = TippingSettingsStorage.shared.paypalReaderTippingStyle
        return [
            InteractiveSection(
                title: "Zettle Reader Tipping (V1/V2)",
                rows: [
                    InteractiveRow(
                        tippingStyle: IZZettleReaderTippingStyle.none,
                        selectedTippingId: selectedZettleTipping
                    ),
                    InteractiveRow(
                        tippingStyle: IZZettleReaderTippingStyle.marketDefault,
                        selectedTippingId: selectedZettleTipping
                    ),
                    InteractiveRow(
                        tippingStyle: IZZettleReaderTippingStyle.amount,
                        selectedTippingId: selectedZettleTipping
                    ),
                    InteractiveRow(
                        tippingStyle: IZZettleReaderTippingStyle.percentage,
                        selectedTippingId: selectedZettleTipping
                    )
                ]
            ),
            InteractiveSection(
                title: "PayPal Reader",
                rows: [
                    InteractiveRow(
                        tippingStyle: IZPayPalReaderTippingStyle.none,
                        selectedTippingId: selectedPayPalTipping
                    ),
                    InteractiveRow(
                        tippingStyle: IZPayPalReaderTippingStyle.marketDefault,
                        selectedTippingId: selectedPayPalTipping
                    ),
                    InteractiveRow(
                        tippingStyle: IZPayPalReaderTippingStyle.customAmount,
                        selectedTippingId: selectedPayPalTipping
                    ),
                    InteractiveRow(
                        tippingStyle: IZPayPalReaderTippingStyle.predefinedPercentage,
                        selectedTippingId: selectedPayPalTipping
                    ),
                    InteractiveRow(
                        tippingStyle: IZPayPalReaderTippingStyle.sdkConfigured,
                        selectedTippingId: selectedPayPalTipping
                    )
                ]
            ),
            InteractiveSection(
                title: "PayPal Reader Presets",
                rows: [
                    InteractiveRow(title: "Nullify presets", action: { TippingSettingsStorage.shared.paypalReaderPredefinedTips = nil }),
                    InteractiveRow(title: "Use default presets", action: { TippingSettingsStorage.shared.paypalReaderPredefinedTips = [ 15, 20, 25 ] }),

                    InteractiveRow(
                        presetNumber: 1,
                        value: TippingSettingsStorage.shared.paypalReaderPredefinedTips?[0],
                        action: { [weak self] in self?.showPresetEditor(presetNumber: 1) }
                    ),
                    InteractiveRow(
                        presetNumber: 2,
                        value: TippingSettingsStorage.shared.paypalReaderPredefinedTips?[1],
                        action: { [weak self] in self?.showPresetEditor(presetNumber: 2) }
                    ),
                    InteractiveRow(
                        presetNumber: 3,
                        value: TippingSettingsStorage.shared.paypalReaderPredefinedTips?[2],
                        action: { [weak self] in self?.showPresetEditor(presetNumber: 3) }
                    )
                ]
            )
        ]
    }

    override func numberOfSections(in tableView: UITableView) -> Int {
        dataSource.count
    }

    override func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        dataSource[section].rows.count
    }

    override func tableView(_ tableView: UITableView, titleForHeaderInSection section: Int) -> String? {
        dataSource[section].title
    }

    override func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let item = dataSource[indexPath.section].rows[indexPath.row]
        let cell: UITableViewCell
        switch indexPath.section {
        case 0, 1:
            cell = UITableViewCell(style: .default, reuseIdentifier: "TippingCell")
            cell.textLabel?.text = item.title
            cell.accessoryType = item.isSelected ? .checkmark : .none
        case 2:
            cell = UITableViewCell(style: .value1, reuseIdentifier: "TippingDetailsCell")
            cell.textLabel?.text = item.title
            cell.detailTextLabel?.text = item.subtitle
        default:
            cell = UITableViewCell(style: .default, reuseIdentifier: "N/A")
            cell.textLabel?.text = "N/A"
        }
        return cell
    }

    override func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
        tableView.deselectRow(at: indexPath, animated: true)
        let row = dataSource[indexPath.section].rows[indexPath.row]
        switch indexPath.section {
        case 0:
            TippingSettingsStorage.shared.zettleReaderTippingStyle = row.elementId
        case 1:
            TippingSettingsStorage.shared.paypalReaderTippingStyle = row.elementId
        case 2:
            row.action?()
        default:
            break
        }
        dataSource = dataSourceWithSelectedOption()
        tableView.reloadData()
    }

    private func showPresetEditor(presetNumber: UInt) {
        let alertController = UIAlertController(
            title: "Edit preset \(presetNumber)",
            message: "Enter new preset value",
            preferredStyle: .alert
        )

        alertController.addTextField { textField in
            textField.keyboardType = .decimalPad
            textField.font = UIFont.monospacedDigitSystemFont(ofSize: 20, weight: .regular)
        }

        alertController.addAction(UIAlertAction(title: "Cancel", style: .cancel))

        alertController.addAction(UIAlertAction(title: "Save", style: .default, handler: { [weak self] _ in
            guard let self else { return }
            let presetString = alertController.textFields!.first!.text!
            let presetValue = NSDecimalNumber(string: presetString, locale: Locale.current)

            var currentPresets = TippingSettingsStorage.shared.paypalReaderPredefinedTips ?? [0, 0, 0]
            currentPresets[Int(presetNumber) - 1] = presetValue.uintValue
            TippingSettingsStorage.shared.paypalReaderPredefinedTips = currentPresets

            self.dataSource = self.dataSourceWithSelectedOption()
            self.tableView.reloadData()
        }))

        present(alertController, animated: true)
    }
}

extension IZZettleReaderTippingStyle {

    var title: String {
        switch self {
        case .none:          "None"
        case .marketDefault: "Market default"
        case .amount:        "Amount"
        case .percentage:    "Percentage"
        @unknown default:    "None"
        }
    }
}

extension IZPayPalReaderTippingStyle {

    var title: String {
        switch self {
        case .none:                 "None"
        case .marketDefault:        "Market default"
        case .customAmount:         "Custom amount"
        case .predefinedPercentage: "Predefined Percentage"
        case .sdkConfigured:        "SDK configured"
        @unknown default:           "None"
        }
    }
}
