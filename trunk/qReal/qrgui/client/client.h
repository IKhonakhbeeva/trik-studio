#pragma once

#include "../kernel/definitions.h"
#include "classes/logicObject.h"

#include <QVariant>
#include <QHash>
#include <QtXml/QDomDocument>

namespace qReal {

	namespace client {

		const QString saveDirName = "./save";

		class Client
		{
		public:
			Client();
			~Client();
			IdTypeList children(const IdType &id) const;
			IdTypeList parents(const IdType &id) const;
			void addParent(const IdType &id, const IdType &parent);
			void addChild(const IdType &id, const IdType &child);
			void removeParent(const IdType &id, const IdType &parent);
			void removeChild(const IdType &id, const IdType &child);
			void setProperty(const IdType &id, const PropertyName &name, const QVariant &value);
			QVariant property(const IdType &id, const PropertyName &name) const;
			void removeProperty(const IdType &id, const PropertyName &name);
			void svnUpdate();
			void svnCommit();

			void printDebug() const;

		private:
			void loadFromDisk();
			void saveToDisk();

			// TODO: Вынести всё, что относится к сериализации, в отдельный класс,
			// как только это переложат в qrgui.
			void loadFromDisk(QString const &currentPath);
			QDomDocument loadXmlDocument(QString const &path);
			void addChildrenToRootObject();

			static LogicObject *parseLogicObject(QDomElement const &elem);
			static QVariant parseValue(QString const &typeName, QString const &valueStr);
			static IdTypeList loadIdList(QDomElement const &elem, QString const &name);
			static bool loadProperties(QDomElement const &elem, LogicObject &object);
			static QPointF parsePointF(QString const &str);

			static void clearDir(QString const &path);
			static QString serializeQVariant(QVariant const &v);
			static QString serializeQPointF(QPointF const &p);
			static QString serializeQPolygon(QPolygon const &p);
			static QString createDirectory(Id const &id);
			static QDomElement idListToXml(QString const &attributeName, IdTypeList const &idList, QDomDocument &doc);
			static QDomElement propertiesToXml(LogicObject * const object, QDomDocument &doc);

			QHash<IdType, LogicObject*> mObjects;
		};

	}

}
