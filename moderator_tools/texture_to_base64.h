#ifndef TEXTURE_TO_BASE64_H
#define TEXTURE_TO_BASE64_H
#include "i_tool.h"
#include <QMap>
#include <QSqlDatabase>

class TextureToBase64 : public ITool
{
public:
    TextureToBase64(const QSqlDatabase& database = QSqlDatabase::database());

    virtual bool setOptionFromComandLine(const QMap<QString, QString>& comand_line_option, QString& error) override;
    virtual bool work(QString& error) override;

    static QString textureToBase64(QString path_to_file, bool * was_ok = nullptr);
    static QByteArray Base64ToTexture(QString base64, bool * was_ok = nullptr);

private:
    QString m_name;
    QString m_texture;

    QSqlDatabase m_database;
};

#endif // TEXTURE_TO_BASE64_H
