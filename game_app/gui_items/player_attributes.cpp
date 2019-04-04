#include "player_attributes.h"

#include "texture.h"
#include "plate_mesh.h"

PlayerAttributes::PlayerAttributes(QObject *parent)
{
    m_progres_bar = new ProgresBar;
    m_progres_bar->setColorBackground(QColor(140, 140, 140));
    m_progres_bar->setColorStatus(QColor(0, 255, 0));

    m_level_background = new OpenGLObject2D();
    m_level_background->setMesh(new PlateMesh());
    m_level_background->setTexture(new Texture(QString(":/resources/level.png")));
    m_level_background->setPosition(20, 20);

    m_level_text = new OpenGLTextRender2D;
    m_level_text->setFontName("Arial.ttf");
    m_level_text->setFontSize(20);
    m_level_text->setColorText(QColor(0,0,0));
    m_level_text->setTextRender("--");

    m_point_to_distribution_value = new OpenGLTextRender2D;
    m_point_to_distribution_value->setFontName("Arial.ttf");
    m_point_to_distribution_value->setFontSize(20);
    m_point_to_distribution_value->setColorText(QColor(255,255,255));
    m_point_to_distribution_value->setTextRender("--");

    m_point_to_distribution_icon = new OpenGLObject2D();
    m_point_to_distribution_icon->setMesh(new PlateMesh());
    m_point_to_distribution_icon->setBaseColor(QColor(120, 120, 120));
    m_point_to_distribution_icon->setTexture(new Texture(QString(":/resources/point_to_distribution.png")));

    m_points_experience = new OpenGLTextRender2D;  // -> [experience] / [experience_to_next_level]
    m_points_experience->setFontName("Arial.ttf");
    m_points_experience->setFontSize(12);
    m_points_experience->setColorText(QColor(255,255,255));
    m_points_experience->setTextRender("--/--");
}

PlayerAttributes::~PlayerAttributes()
{

}

void PlayerAttributes::setPosition(const QVector2D& pos)
{
    m_position = pos;

    resize();
}

void PlayerAttributes::setSize(const QVector2D& size)
{
    m_size = size;

    resize();
}

bool PlayerAttributes::draw(Shader* shader)
{
    m_progres_bar->draw(shader);
    m_point_to_distribution_icon->draw(shader);
    m_point_to_distribution_value->draw(shader);
    m_points_experience->draw(shader);
    m_level_background->draw(shader);
    m_level_text->draw(shader);

    return true;
}

void PlayerAttributes::loadPlayerFromServer()
{
    args.setArg(GetPlayerInfoLogicArgs::ArgumentsQuery::ID_GAMER, PlayerInfo::getIdPlayer());

    qDebug() << __PRETTY_FUNCTION__ << " QUERY: " << args.getQuery();
    emit sendToServer(args.getQuery());
}

void PlayerAttributes::loadPlayerFromPLayerInfo(const PlayerInfo& info)
{
    if(info.getIdPlayer() == -1)
        return;

    m_points_to_distribution = info.getPointsToDistribution();

    refreshPointsToDistributionOnView(m_points_to_distribution);

    m_level_text->setTextRender(QString::number(info.getLevel()));
    m_point_to_distribution_value->setTextRender(QString::number(info.getPointsToDistribution()));
    m_points_experience->setTextRender(QString::number(info.getExperience()) + " / " + QString::number(info.getExperienceToNextLevel()));

    m_progres_bar->setStatus(static_cast<float>(info.getExperience()) / static_cast<float>(info.getExperienceToNextLevel()));
}

void PlayerAttributes::mouseEventRec(QEvent::Type type, QVector2D pos, Qt::MouseButton button)
{
    Q_UNUSED(type);
    Q_UNUSED(pos);
    Q_UNUSED(button);
}

void PlayerAttributes::kayboardEventRec(QEvent::Type type, Qt::Key key, QString text)
{
    Q_UNUSED(type);
    Q_UNUSED(key);
    Q_UNUSED(text);
}

void PlayerAttributes::receiveFromServer(const QString& response)
{
    if(args.setResponse(response))
    {
        qDebug() << __PRETTY_FUNCTION__ << " RESPONSE: " << response;
        PlayerInfo player_info;
        player_info.setName(args.getArg(GetPlayerInfoLogicArgs::ArgumentsResponse::NAME).toString());
        player_info.setLevel(args.getArg(GetPlayerInfoLogicArgs::ArgumentsResponse::LEVEL).toInt());
        player_info.setExperience(args.getArg(GetPlayerInfoLogicArgs::ArgumentsResponse::EXPERIENCE).toLongLong());
        player_info.setExperienceToNextLevel(args.getArg(GetPlayerInfoLogicArgs::ArgumentsResponse::EXPERIENCE_TO_NEXT_LEVEL).toLongLong());
        player_info.setPointsToDistribution(args.getArg(GetPlayerInfoLogicArgs::ArgumentsResponse::POINTS_TO_DISTRIBUTION).toInt());

        loadPlayerFromPLayerInfo(player_info);
    }
}

void PlayerAttributes::minusClicked()
{
    m_points_to_distribution++;

    refreshPointsToDistributionOnView(m_points_to_distribution);
}

void PlayerAttributes::plusClicked()
{
    if(m_points_to_distribution == 0)
        return;

    m_points_to_distribution--;

    refreshPointsToDistributionOnView(m_points_to_distribution);
}

void PlayerAttributes::anulujClicked()
{
    m_points_to_distribution = PlayerInfo::getPointsToDistribution();

    refreshPointsToDistributionOnView(m_points_to_distribution);
}

void PlayerAttributes::saveClicked(CreatureInfo creature)
{
    Q_UNUSED(creature);

    PlayerInfo::setPointsToDistribution(m_points_to_distribution);

    refreshPointsToDistributionOnView(m_points_to_distribution);
}

void PlayerAttributes::refreshPointsToDistributionOnView(int points)
{
    if(points > 0)
    {
        m_point_to_distribution_value->setVisible(true);
        m_point_to_distribution_value->setTextRender(QString::number(points));
        m_point_to_distribution_icon->setVisible(true);

        emit existPoints(true);
    }
    else
    {
        m_point_to_distribution_value->setVisible(false);
        m_point_to_distribution_icon->setVisible(false);

        emit existPoints(false);
    }
}

void PlayerAttributes::resize()
{
    m_progres_bar->setSize(QVector2D(m_size.x(), 20));
    m_level_background->setScale(m_size.y() * 2, m_size.y() * 2); //it is not mistake

    m_progres_bar->setPosition(QVector2D(m_position.x() + m_size.y() - 5, m_position.y() + m_size.y() - (m_size.y()/ 2) + 10));
    m_level_text->setPosition(m_position.x() + m_size.y() - 5, m_position.y() + m_size.y() + 10); //it is not mistake

    m_points_experience->setPosition(m_position.x() + m_size.x() - 50, m_position.y() + 25);
    m_level_background->setPosition(m_position.x(), m_position.y());

    m_point_to_distribution_icon->setPosition(m_points_experience->getPosition().x(), m_points_experience->getPosition().y() + 30);
    m_point_to_distribution_icon->setScale(70, 70);

    m_point_to_distribution_value->setPosition(m_point_to_distribution_icon->getPosition().x() + 30, m_point_to_distribution_icon->getPosition().y() + 35);
}
