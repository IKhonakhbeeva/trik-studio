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

#include "customKitInterpreterPlugin.h"
#include <qrutils/smartDock.h>

#include <QtWidgets/QApplication>

using namespace customKitInterpreter;

CustomKitInterpreterPlugin::CustomKitInterpreterPlugin()
	: mRobotModel(kitId())
    , mCustomWidget(new view::CustomWidget())
    , mDock(new utils::SmartDock("2dModelDock", mCustomWidget))
{
}

CustomKitInterpreterPlugin::~CustomKitInterpreterPlugin()
{
	delete mCustomWidget;
}

void CustomKitInterpreterPlugin::init(const kitBase::KitPluginConfigurator &configurer)
{
	configurer.qRealConfigurator().mainWindowDockInterface().registerEditor(*mCustomWidget);
//	const auto onActiveTabChanged = [this](const qReal::TabInfo &info) {
//		mCustomWidget->setEnabled(info.type() != qReal::TabInfo::TabType::other);
//	};
//	connect(&configurer.qRealConfigurator().systemEvents(), &qReal::SystemEvents::activeTabChanged, this, onActiveTabChanged);

	connect(&configurer.eventsForKitPlugin(),
			&kitBase::EventsForKitPluginInterface::robotModelChanged,
			this,
			[this](const QString &modelName) {
				const bool isCurrentModel = modelName == mRobotModel.name();
				if (isCurrentModel) {
					mDock->attachToMainWindow(Qt::TopDockWidgetArea);
				} else {
					mDock->detachFromMainWindow();
				}
			});
}

QString CustomKitInterpreterPlugin::kitId() const
{
	return "customKit";
}

QString CustomKitInterpreterPlugin::friendlyKitName() const
{
	return tr("Custom Kit");
}

QList<kitBase::robotModel::RobotModelInterface *> CustomKitInterpreterPlugin::robotModels()
{
	return QList<kitBase::robotModel::RobotModelInterface *>() << &mRobotModel;
}

QSharedPointer<kitBase::blocksBase::BlocksFactoryInterface> CustomKitInterpreterPlugin::blocksFactoryFor(
		const kitBase::robotModel::RobotModelInterface *model)
{
	Q_UNUSED(model)
	return nullptr;
}

QList<kitBase::AdditionalPreferences *> CustomKitInterpreterPlugin::settingsWidgets()
{
	return {nullptr};
}

QList<qReal::ActionInfo> CustomKitInterpreterPlugin::customActions()
{
	return {};
}

QList<qReal::HotKeyActionInfo> CustomKitInterpreterPlugin::hotKeyActions()
{
	return {};
}

QIcon CustomKitInterpreterPlugin::iconForFastSelector(
		const kitBase::robotModel::RobotModelInterface &robotModel) const
{
	Q_UNUSED(robotModel)
	return QIcon();
}
