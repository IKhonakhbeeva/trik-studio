#include "nullKitInterpreterPlugin.h"

#include <QtWidgets/QApplication>

using namespace nullKitInterpreter;

NullKitInterpreterPlugin::NullKitInterpreterPlugin()
{
	mAppTranslator.load(":/nullKitInterpreter_" + QLocale::system().name());
	QApplication::installTranslator(&mAppTranslator);
}

QString NullKitInterpreterPlugin::kitId() const
{
	return "nullKit";
}

QString NullKitInterpreterPlugin::friendlyKitName() const
{
	return tr("Empty Kit");
}

QList<interpreterBase::robotModel::RobotModelInterface *> NullKitInterpreterPlugin::robotModels()
{
	return QList<interpreterBase::robotModel::RobotModelInterface *>() << &mRobotModel;
}

interpreterBase::blocksBase::BlocksFactoryInterface *NullKitInterpreterPlugin::blocksFactoryFor(
		interpreterBase::robotModel::RobotModelInterface const *model)
{
	Q_UNUSED(model)
	return nullptr;
}

interpreterBase::AdditionalPreferences *NullKitInterpreterPlugin::settingsWidget()
{
	return nullptr;
}

//QList<QWidget *> NullKitInterpreterInterface::toolWidgets() const
//{
//	return QList<QWidget *>();
//}

QList<qReal::ActionInfo> NullKitInterpreterPlugin::customActions()
{
	return {};
}

QIcon NullKitInterpreterPlugin::iconForFastSelector(
		interpreterBase::robotModel::RobotModelInterface const &robotModel) const
{
	Q_UNUSED(robotModel)
	return QIcon();
}
