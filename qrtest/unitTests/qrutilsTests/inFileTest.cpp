/* Copyright 2007-2015 QReal Research Group
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

#include <QtCore/QFile>

#include <qrutils/inFile.h>

#include "gtest/gtest.h"

TEST(InFileTest, readAllTest)
{
	QFile file("testFile");
	file.open(QIODevice::ReadWrite);

	file.write("text1\n");
	file.write("text2\n");
	file.write("text3\n");
	file.close();

	QString dataRead = utils::InFile::readAll("testFile");

	EXPECT_EQ(dataRead, "text1\ntext2\ntext3\n");

	QFile::remove("testFile");
}
