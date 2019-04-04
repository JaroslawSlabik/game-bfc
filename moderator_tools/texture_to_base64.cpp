#include "texture_to_base64.h"
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>
#include <QFileInfo>

TextureToBase64::TextureToBase64(const QSqlDatabase& database)
{
    m_database = database;
}

bool TextureToBase64::setOptionFromComandLine(const QMap<QString, QString>& comand_line_option, QString& error)
{
    qDebug() << "You choice tool: TextureToBase64";

    m_name = comand_line_option.value("n", "");
    if(true == m_name.isEmpty())
    {
        error += "Name is empty";
        return false;
    }

    m_texture = comand_line_option.value("x", "");
    if(true == m_texture.isEmpty())
    {
        error += "Texture is empty";
        return false;
    }

    QFileInfo check_texture_file(m_texture);
    if(false == check_texture_file.exists() || false == check_texture_file.isFile())
    {
        error += "Texture file not exists";
        return false;
    }

    return true;
}

bool TextureToBase64::work(QString& error)
{
    bool was_ok = false;

    QString texture_base64 = this->textureToBase64(m_texture, &was_ok);
    if(false == was_ok)
    {
        error = "Error during convert file to texture in Base64";
        return false;
    }

    QFile file(m_name);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    out << texture_base64;
    file.close();

    qDebug() << "Texture is export to file in Base64";

    return true;
}

QString TextureToBase64::textureToBase64(QString path_to_file, bool * was_ok)
{
    *was_ok = true;

    QFileInfo check_texture_file(path_to_file);
    if(false == check_texture_file.exists() || false == check_texture_file.isFile())
    {
        *was_ok = false;
        return "";
    }

    QImage img_enrll(path_to_file);
    QByteArray arr;
    QBuffer buffer(&arr);
    *was_ok = buffer.open(QIODevice::WriteOnly);
    if(false == *was_ok)
    {
        *was_ok = false;
        return "";
    }

    *was_ok = img_enrll.save(&buffer, "PNG");
    if(false == *was_ok)
    {
        *was_ok = false;
        return "";
    }

    *was_ok = true;
    return arr.toBase64();
}

QByteArray TextureToBase64::Base64ToTexture(QString base64, bool * was_ok)
{
    return QByteArray::fromBase64(base64.toUtf8());
}
