#pragma once

#include <QtCore/QScopedPointer>

#include <kitBase/kitPluginInterface.h>
#include <twoDModel/engine/twoDModelControlInterface.h>

#include "trikAdditionalPreferences.h"
#include "trikFSharpAdditionalPreferences.h"

#include <trikKit/blocks/trikBlocksFactory.h>
#include "robotModel/real/realRobotModelV6.h"
#include "robotModel/twoD/twoDRobotModel.h"

namespace trik {

class TrikKitInterpreterPlugin : public QObject, public kitBase::KitPluginInterface
{
	Q_OBJECT
	Q_INTERFACES(kitBase::KitPluginInterface)
	Q_PLUGIN_METADATA(IID "nxtKitInterpreter.TrikKitInterpreterPlugin")

public:
	TrikKitInterpreterPlugin();
	~TrikKitInterpreterPlugin() override;

	void init(const kitBase::EventsForKitPluginInterface &eventsForKitPlugin
			, const qReal::SystemEvents &systemEvents
			, qReal::GraphicalModelAssistInterface &graphicalModel
			, qReal::LogicalModelAssistInterface &logicalModel
			, qReal::gui::MainWindowInterpretersInterface &interpretersInterface
			, kitBase::InterpreterControlInterface &interpreterControl) override;

	QString kitId() const override;
	QString friendlyKitName() const override;

	QList<kitBase::robotModel::RobotModelInterface *> robotModels() override;
	kitBase::robotModel::RobotModelInterface *defaultRobotModel() override;

	kitBase::blocksBase::BlocksFactoryInterface *blocksFactoryFor(
			const kitBase::robotModel::RobotModelInterface *model) override;

	// Transfers ownership.
	QList<kitBase::AdditionalPreferences *> settingsWidgets() override;
	QWidget *quickPreferencesFor(const kitBase::robotModel::RobotModelInterface &model) override;
	QString defaultSettingsFile() const override;
	QIcon iconForFastSelector(const kitBase::robotModel::RobotModelInterface &robotModel) const override;
	kitBase::DevicesConfigurationProvider * devicesConfigurationProvider() override;

	QList<qReal::ActionInfo> customActions() override;
	QList<qReal::HotKeyActionInfo> hotKeyActions() override;


private slots:
	/// Shows or hides 2d model action depending on whether current tab is robots diagram.
	void onActiveTabChanged(const qReal::Id &rootElementId);

private:
	QScopedPointer<twoDModel::TwoDModelControlInterface> mTwoDModelV6;
	robotModel::real::RealRobotModelV6 mRealRobotModelV6;
	robotModel::twoD::TwoDRobotModel mTwoDRobotModelV6;

	/// @todo Use shared pointers instead of this sh~.
	blocks::TrikBlocksFactory *mBlocksFactory = nullptr;  // Transfers ownership
	bool mOwnsBlocksFactory = true;

	TrikAdditionalPreferences *mAdditionalPreferences = nullptr;  // Transfers ownership
	TrikFSharpAdditionalPreferences *mFSharpAdditionalPreferences = nullptr;  //Transfers ownership
	bool mOwnsAdditionalPreferences = true;

	QWidget *mIpAdressQuickConfigurer = nullptr;  // Transfers ownership
	bool mOwnsIpAdressQuickConfigurer = true;

	kitBase::InterpreterControlInterface *mInterpreterControl;  // Does not have ownership.
	QString mCurrentlySelectedModelName;
};

}
