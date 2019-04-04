#include "create_battle_map.h"
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>
#include <QFileInfo>

#include "texture_to_base64.h"

CreateBattleMap::CreateBattleMap(const QSqlDatabase& database)
{
    m_database = database;
}

bool CreateBattleMap::setOptionFromComandLine(const QMap<QString, QString>& comand_line_option, QString& error)
{
    qDebug() << "You choice tool: CreateBattleMap";

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

    m_map = comand_line_option.value("m", "");
    if(true == m_map.isEmpty())
    {
        error += "Map is empty";
        return false;
    }

    QFileInfo check_map_file(m_map);
    if(false == check_map_file.exists() || false == check_map_file.isFile())
    {
        error += "Map file not exists";
        return false;
    }

    m_id_element = comand_line_option.value("e", "").toInt(&was_ok);
    if(1 > m_id_element || false == was_ok)
    {
        error += "ID element is empty";
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

bool CreateBattleMap::work(QString& error)
{
    bool was_ok = false;

    QString texture_base64 = TextureToBase64::textureToBase64(m_texture, &was_ok);
    if(false == was_ok)
    {
        error = "Error during convert file to texture in Base64";
        return false;
    }

    QString map_convert = convertMapToMyType(m_map, &was_ok);
    if(false == was_ok)
    {
        error = "Error during convert map";
        return false;
    }

    QString map = map_convert + texture_base64;

    QSqlQuery query(m_database);
    QString exec_query = QString("SELECT * FROM add_new_map(%1, '%2', '%3', '%4');")
            .arg(m_id_element)
            .arg(m_name)
            .arg(m_description)
            .arg(map);
    if(false == query.exec(exec_query))
    {
        error = "Error during exec query: " + exec_query + "\nError: " + query.lastError().text();
        return false;
    }

    qDebug() << "Map is added";

    return true;
}

QString CreateBattleMap::convertMapToMyType(QString path_to_map, bool* was_ok)
{
    *was_ok = true;

    QFileInfo check_texture_file(path_to_map);
    if(false == check_texture_file.exists() || false == check_texture_file.isFile())
    {
        *was_ok = false;
        return "";
    }

    QFile file(path_to_map);
    if(false == file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        *was_ok = false;
        return "";
    }

    int x_size_field = 40;
    int y_size_field = 40;

    int x_size_map = 0;
    int y_size_map = 0;
    QString map = "";
    QTextStream in(&file);
    while(false == in.atEnd())
    {
        QString line = in.readLine();
        x_size_map = line.length();
        int count = 0;
        QChar last_char = line.at(0);
        QString line_tmp = "";
        for(int i = 0; i < x_size_map; /**/)
        {
            if(last_char != line.at(i))
            {
                if(1 < count)
                {
                    map += QString::number(count);
                }

                map += last_char;


                last_char = line.at(i++);
                count = 1;
            }
            else
            {
                i++;
                count++;
            }
        }

        if(1 < count)
        {
            map += QString::number(count);
        }

        map += last_char;

        map += "-";

        y_size_map++;
    }

    map.chop(1);

    map =
        QString::number(x_size_map) + " " + QString::number(y_size_map) + "+" +
        QString::number(x_size_field) + " " + QString::number(y_size_field) + "+" +
        map + "+";

    *was_ok = true;
    return map;
}

