/* Copyright 2007-2015 QReal Research Group, Dmitry Mordvinov
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

#include "interpreterCore/customizer.h"

#include <QtWidgets/QApplication>

#include <qrkernel/settingsManager.h>
#include <qrkernel/platformInfo.h>

using namespace interpreterCore;

QString Customizer::windowTitle() const
{
	return qReal::SettingsManager::value("MainWindowTitle"
				  , QObject::tr("TRIK Studio") + " " + productVersion())
		.toString();
}

QIcon Customizer::applicationIcon() const
{
	return QIcon(":/icons/icon.png");
}

QImage Customizer::applicationLogo() const
{
	return QImage(":/icons/TRIKStudioLogo.png");
}

QString Customizer::productVersion() const
{
	return trikStudioVersion();
}

QString Customizer::aboutText() const
{
	return "http://www.trikset.com/products/trik-studio";
}

QString Customizer::examplesDirectory() const
{
	return qReal::PlatformInfo::invariantSettingsPath("pathToExamples");
}

QString Customizer::trikStudioVersion()
{
	return TRIK_STUDIO_VERSION;
}

QList<QPair<QString, qReal::ActionVisibility> > Customizer::actionsVisibility() const
{
	return {
		{ "actionNew_Diagram", qReal::ActionVisibility::VisibleOnlyInMenu }
		, { "actionFullscreen", qReal::ActionVisibility::Invisible }
	};
}

bool Customizer::showInterpeterButton() const
{
	return false;
}

bool Customizer::allowSubprogramPropertiesChanging() const
{
	return true;
}

QString Customizer::userPaletteTitle() const
{
	return QObject::tr("Subprograms");
}

QString Customizer::userPaletteDescription() const
{
	return QObject::tr("The list of all declared subprograms in the project");
}
