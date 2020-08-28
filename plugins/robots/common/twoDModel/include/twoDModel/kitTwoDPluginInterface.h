/* Copyright 2020 CyberTech Labs Ltd.
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

#include "twoDModel/engine/twoDModelEngineFacade.h"

namespace twoDModel {

/// Plugin interface for a kit support plugin.
class KitTwoDPluginInterface
{
	Q_DISABLE_COPY(KitTwoDPluginInterface)
public:
	KitTwoDPluginInterface() = default;

	virtual ~KitTwoDPluginInterface() = default;

	virtual void setTwoDModelEngineFacade(twoDModel::engine::TwoDModelEngineFacade * modelEngine) = 0;
	virtual robotModel::TwoDRobotModel & twoDRobotModel() = 0;
};

}

Q_DECLARE_INTERFACE(twoDModel::KitTwoDPluginInterface, "ru.spbsu.math.QReal.KitTwoDPluginInterface/1")
