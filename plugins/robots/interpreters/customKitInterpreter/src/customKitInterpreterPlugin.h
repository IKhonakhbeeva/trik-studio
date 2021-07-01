/* Copyright 2021 CyberTech Labs Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License. */

#pragma once

#include <kitBase/kitPluginInterface.h>
#include "customRobotModel.h"
#include <qrutils/smartDock.h>
#include "customWidget.h"

namespace customKitInterpreter {

class CustomKitInterpreterPlugin : public QObject, public kitBase::KitPluginInterface
{
	Q_OBJECT
	Q_INTERFACES(kitBase::KitPluginInterface)
	Q_PLUGIN_METADATA(IID "custom.CustomKitInterpreterPlugin")

public:
	CustomKitInterpreterPlugin();
	~CustomKitInterpreterPlugin() override;

	QString kitId() const override;

	QString friendlyKitName() const override;

	QList<kitBase::robotModel::RobotModelInterface *> robotModels() override;

	QSharedPointer<kitBase::blocksBase::BlocksFactoryInterface> blocksFactoryFor(
			const kitBase::robotModel::RobotModelInterface *model) override;

	// Transfers ownership.
	QList<kitBase::AdditionalPreferences *> settingsWidgets() override;

	QList<qReal::ActionInfo> customActions() override;

	QList<qReal::HotKeyActionInfo> hotKeyActions() override;

	QIcon iconForFastSelector(const kitBase::robotModel::RobotModelInterface &robotModel) const override;

	void init(const kitBase::KitPluginConfigurator &configurer) override;

private:
	CustomRobotModel mRobotModel;
	view::CustomWidget *mCustomWidget;
	utils::SmartDock *mDock;
};

}
