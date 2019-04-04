#include "create_creature.h"
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>
#include <QFileInfo>

#include "texture_to_base64.h"

CreateCreature::CreateCreature(const QSqlDatabase& database)
{
    m_database = database;
}

bool CreateCreature::setOptionFromComandLine(const QMap<QString, QString>& comand_line_option, QString& error)
{
    qDebug() << "You choice tool: CreateCreature";

    bool was_ok = false;
    m_name = comand_line_option.value("n", "");
    if(true == m_name.isEmpty())
    {
        error += "Name is empty";
        return false;
    }

    m_description = comand_line_option.value("d", "");
    if(true == m_description.isEmpty())
    {
        error += "Description is empty";
        return false;
    }

    m_health = comand_line_option.value("h", "").toInt(&was_ok);
    if(1 > m_health || false == was_ok)
    {
        error += "Health is empty";
        return false;
    }

    m_shield = comand_line_option.value("s", "").toInt(&was_ok);
    if(1 > m_shield || false == was_ok)
    {
        error += "Shield is empty";
        return false;
    }

    m_attack = comand_line_option.value("a", "").toInt(&was_ok);
    if(1 > m_attack || false == was_ok)
    {
        error += "Attack is empty";
        return false;
    }

    m_point_move = comand_line_option.value("p", "").toInt(&was_ok);
    if(1 > m_point_move || false == was_ok)
    {
        error += "Point is empty";
        return false;
    }

    m_method_move = comand_line_option.value("v", "").toInt(&was_ok);
    if(1 > m_method_move || false == was_ok)
    {
        error += "Method of move is empty";
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

bool CreateCreature::work(QString& error)
{
    bool was_ok = false;

    QString texture_base64 = TextureToBase64::textureToBase64(m_texture, &was_ok);
    if(false == was_ok)
    {
        error = "Error during convert file to texture in Base64";
        return false;
    }

    QSqlQuery query(m_database);
    QString exec_query = QString("SELECT * FROM add_new_creature(%1, '%2', '%3', '%4', %5, %6, %7, %8);")
            .arg(m_method_move)
            .arg(m_name)
            .arg(m_description)
            .arg(texture_base64)
            .arg(m_health)
            .arg(m_shield)
            .arg(m_attack)
            .arg(m_point_move);
    if(false == query.exec(exec_query))
    {
        error = "Error during exec query: " + exec_query + "\nError: " + query.lastError().text();
        return false;
    }

    qDebug() << "Creature is added";

    return true;
}
