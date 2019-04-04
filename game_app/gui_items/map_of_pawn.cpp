#include "map_of_pawn.h"

MapOfPawn::MapOfPawn(QObject *parent)
{
    m_selected_pawn = std::make_pair(-1, -1);
    m_selected_cell = std::make_pair(-1, -1);
    m_selected_enemy_pawn = std::make_pair(-1, -1);
    m_do_something = false;
}

MapOfPawn::~MapOfPawn()
{
    m_map_of_pawn.clear();
}

void MapOfPawn::setPositionPawn(int x, int y, int new_x, int new_y)
{
    Pawn* selected_pawn = m_map_of_pawn.value(std::make_pair(x, y), nullptr);
    if(nullptr == selected_pawn)
    {
        //pionek nie istnieje
        return;
    }

    Pawn* possible_pawn = m_map_of_pawn.value(std::make_pair(new_x, new_y), nullptr);
    if(nullptr != possible_pawn )
    {
        if(false == possible_pawn->getInfo().m_enemy)
        {
            // na nowym miejscu jest pionek który nie jest przeciwnikiem
            return;
        }
    }

    selected_pawn->setPosition(m_position_map.x() + (new_x * m_size_cell.x()), m_position_map.y() + (new_y * m_size_cell.y()));

    m_map_of_pawn.remove(std::make_pair(x, y));
    m_map_of_pawn.insert(std::make_pair(new_x, new_y), selected_pawn);
}

void MapOfPawn::movePawnBaseVector(int x, int y, std::pair<int, int> vector)
{
    Pawn* selected_pawn = m_map_of_pawn.value(std::make_pair(x, y), nullptr);
    if(nullptr == selected_pawn)
    {
        //pionek nie istnieje
        return;
    }

    int new_x = x + vector.first;
    int new_y = y + vector.second;

    if(nullptr != m_map_of_pawn.value(std::make_pair(new_x, new_y), nullptr))
    {
        // na nowym miejscu jest pionek
        return;
    }

    selected_pawn->setPosition(m_position_map.x() + (new_x * m_size_cell.x()), m_position_map.y() + (new_y * m_size_cell.y()));

    m_map_of_pawn.remove(std::make_pair(x, y));
    m_map_of_pawn.insert(std::make_pair(new_x, new_y), selected_pawn);
}

bool MapOfPawn::draw(Shader* shader)
{
    for(Pawn* p : m_map_of_pawn.values())
    {
        if(nullptr != p)
        {
            p->draw(shader);
        }
    }

    return true;
}

void MapOfPawn::loadPawnsFromServer()
{

}

void MapOfPawn::kayboardEventRec(QEvent::Type type, Qt::Key key, QString text)
{

}

void MapOfPawn::mouseEventRec(QEvent::Type type, QVector2D pos, Qt::MouseButton button)
{

}

void MapOfPawn::receiveFromServer(const QString& response)
{
    //TODO: response actual pawn
    //init or update m_map_of_pawn
    CreatureInfo info;
    info.m_id = 1;
    info.m_name = "Octo";
    info.m_health = 2;
    info.m_actual_health = 2;
    info.m_shield = 2;
    info.m_actual_shield = 2;
    info.m_attack = 2;
    info.m_point_of_move = 15;
    info.m_actual_move = 15;
    info.m_enemy = true;
    info.m_texture = QByteArray(QByteArray::fromBase64("iVBORw0KGgoAAAANSUhEUgAAADAAAAAwCAYAAABXAvmHAAAACXBIWXMAAA9hAAAPYQGoP6dpAAAQ4UlEQVRoge2ZebReVXnGf3s453zTHZPcTBAhxAAJCSbVaoqkDCIJUqAgplSXWliL2pZWxFZti7YutEutpdQKFaylXWIVsK2KkEsChNEwhzCXkJDx3tyRe7/7fWfcQ/84N8hYUbGrf/CuddZ3vr3evc/z7PfZ77vPPvCmvWn//2zze65/7x1vvW7lgf+3L7ruiJ8cd92Zv4pnydfr+HX+pOMyPjbjZ/kNPnRbvfPd1YtVR6QOtOnOqGi8vfaZwYdu6/tFgb6WvW4CWoRhVXTc/A0+eekVfOI1idgJe2m+Q67Q3XrHC3179O5il+wzI/aqXxbwy+11E/iY/+pYjUbSLfo+URcd91zBhYtf7rNzw42fyve4892EXv+u2943dqD9Xbe+ryDRP853+tN3bbzxK28UePg5CFwvvtpbpfOwKg3qdB2uRfCtr3HBC/13rr/pw1rpL2ePaHzBtwD6V15TX7/i23UAZ/3V6RZlpA/+bFf/TZ94owiI1+t4m/juX+QkXzQUZMSM+UGXky67gK89uXfTht8V0l+dbdXh+EbXHBsZvtcLP99r0RACIYSIBWJ3d0fvyhmrg5mVdxbYxF+wYM2ay/9PCDwm7zom9fGGJmO1FhO0/QTD7JtYfPahxy7/w2W/5727yO3TtDdUGNo3grUGHQbIQCFDCQE44REeeoNuGidkiIU5PuUaa8yfLjzttKFfGYHt8pEjLWZD2zcPGmEvo36AJqPMOWnm6MpPHj2uqiwunhMUd3UyOdQmbaUopRBKIEOJqEpkVUEo8cIhc0GDiPCYKfQiiy/kfluYi02eX73ozDPdG0pgm9zyFoW6NfPJYcN+L0M8hzzccOhH5jH33XNwxlFsVfBoN81Wm3YzRrlySKElsiIRVYWsKUQoQAmcs+i2omEriKOa6LdlCCWxmb3XFMWnDzvjjDvfEAJPy/si5YMNxpvVYwwQHzLCzHPqzFzdie7QFEMO+WAX7KvT9C2mplooJxGIcvYr08AjiQglKAHC4z2YNCdKAjpNHfoS3DsmEDMcZHgVBD+01n5hwdq1D/1SBB7l7ksc7mJ7RJPaRy21JZKwJ8JkOXabRm+dhTARo4zSaraouCrCl7KRDY1qaGRNlfKZLmneeFxmcYklmWoTWMVMMROhDMVRI4jFGRKNL1yuK9ED1pi/OnjNmlt/bgL38KNDq4v0ls6Pii61JCGaWYMCsskY8Xg34e5ZmNAxlA4TxzHaKZRThGFE0BkRzIjQM0JUhy4JSPC2BG9aBdlEQjoRk02k6FwyuzGbio/I5o7glo8TdVXxBkyaFkGt9hOh9WfnnXjiXa+LwMCtm6LmrfEV1WX+XDHLQKaRypOOZoj7Z1FtzSSpp+xvDWHbBbKQSC0RQqCrmnBWlcq8OuHsKrormI6AwDuHSQxmKicfTcmHUvKRhGw8wbYMc2bNpTPqIg3GcO8YJpoT4K3C5jlBGLZFEHxJheEVc447bvzFeF9SyPbcsrEraU2s73qvPFfUC4gVUnvyYYO9bRbhVA9xI2agNYjLLLIQCAdkHlkIpJdIVepeViWyoVBdAaorQHeHhL0RYW+FsLdC0BmiQo3WAcILdj+9k+fbY0SmB3dbH9keiwocSmtsnteFc5e0n3/+lr0bN857VQKDmzYp5fw/hCo43sceRECls0K6LyG7pZswa1DUc/Y3h8CCNAJhBKQe33aQOYQVSAcKiQ4UOgxQYYCuaHQ1QFVDdC0o7yONChVSS5SWKCnZ88hO2ukUoaxTbOqlvSMlaoTIMMRbSxQEK6Rz/zS4aVP1FQRMml7u0vQjEkjimCyPIZFkd/YipiJEBUaaY9jCIjKPTx3krvxNPaQgDJCDKEA4iUCiECitUKoEKqfvpRRIKZFCghMIIfHGs2fLTlAOmYXkd/biJxWFzWi3WkgpsWl6mknTa15CYE9//3Jl7Xl5u40zhkZnB416jeEbM+yARktBq9WincSQgWtbyD3eeDAgLGD8C2R8XP6K3IPxJSFbyk1YwAJGgAXhyzbhQClJPN5mbMcoWgv8mGbkxwUVFdDV040zhrzdRhpz5p7163/zpxEw5nyb5zqoVtGVCiaPGXt4iuwpjfQOnzkmm5P4zOJaFp85vPXgfgqCwkPi8LHDty2+ZSF2kHhIHT6ZjlTmIPeQOyg8/kUXFgSC8T2juNgivSPfrhm7r02eTaHDiLBex+Y5wto/AtC7+/v7pHMfsN4jAW8K8jgje6yOiD2iKsjaGS3XQmkN1uO9BDwCAX56Rj34zOFaBve8wYzmqKoufQoFwmNzh2tb3JTFJ9PyOxAl48GBkIJ2q0V7rEVUixCZI3u8TnF4C9WVIwDnPVKp39q9fv3hWgpxjLd2lpASFQSgHPEuixnQhM4jvWAqbpORUVEC4SVSCDweLz1SCXCAA5843KTBhDmqotGhRuTgahIvwRUOO5VjJnLslMEXDp+7UorOgy83fMZb2s02lWoV4Tx2WNPe7qm8w6FkgHcOb0xFhuFx2sTxgkgpMueYHBxk/pELMQM5ZSYC4QVZnmKFwRmL9IAUeDldRYQqZ9l4vHNYYbC6wAQ5hVKQOkRd4TU44zBTOWYiw00VJXDK6CHEC7deetI0niYlIHOYfRHRcXWGduwlqtWoKUUexwdrHQRvM1lGoDW9c+aQTbbI9zuE86AB78ltPr3aPM55BA6hwCuBx+GsQFpwVkBsMaJAKFH6WI/Mytrg7DSByQLbNnhTbj6FeFFJFeXKzE1eSqrUDPmwJ59s0ds3C2sstihQYXiEFjDXFQXWGKSSJO0WttkAWxLwEiy2lIwtw+ydwzmQXuIpNeycQFqPsx4rQGqBqU4XNREgrcQ5h40tLjXlnsiW8vHTSwkpEIEALzBYvChVgHW4pqC1f4JqTw3vBc4YdBj2am/tY9aYk6POTsDjmh6ycuYPzIgvYeJFScJbD0hCpwlEgHEGUxicBylkqfXcItsGEQikc5AIvPeY1OBSi8olIQGFEBQiB0kJXpRrystSSn5aWD4HlztkFAIKOzmJt3aHRohBHQTkrRZhrVomZG3wLipnCJBC4bzFH5CE0IRCs6X5BHuTQZbUF3NEsJCsyLC+jLtJDX4SHA6ZW0QocKJcrJEJ2Taxg4dHHmVWNIMVnUsJggDjTQnXegIdAAJvHM6C0AYRWLCeImkhtQYpR7T1vklR4J1DKU3UUUV2FxTPOZywOOeoyAhbWHzgUZHC5IYv7vwad7mHaHQ1mNwxwUdmnMUfzPgQhSlw1pY5/0CmKiwiEHgF1aDCvzz7XS578ioqM+tkacoyFvP5wz9JNaiS2xwnLZWggvcOV1hc4dFdOVFXBaU0ubV473HGTEkRhv1SqTGlNZNjY4Ck99cCnDC43GGKgnpQQ1qBERYdBlw18B022fu4dcMtjA+M8cEPf5Crx67nB62NVIMKTngcDmssJjWYpKBIDEGu2bj7Dr7yxOUcv+YERvYO8dC9D/JMZRdffubyMklIh0DQiOqYwmIzizOGrqM1KgyZHBlBKoWUMpPV6g1ywdq1e6nV/l5qTaAURTunvkgSLkoxLYdpF+ggoIMG1hn2Z0P8ePxWVq9azbHHHAvAeeeeB8APJzaQRAWiIvGhwOtSx074cv0Ixw/29gNwzrpzCMOQpUuWsvY9a7izeT874l046ajLOlFYwcQ5tuXQC1I6jhIU7RylFEprRL3+zQVr1z4mAYxSV7ba7R2BUgRaYwpLz0k5dOaYCYN1lp5KDyoX7E9HyCh49pltDA2Vhwn33HMPALuyvYyHE6iOEBqyvGoCqgJZl7TChJ3JHgAeeOABAOI45uknnwZgd7oP5SW9lR4slmKywEeGnpMzLBYlFVEQ0JqaGi2UuhTKTM+hp546OnB7/1lMTn7fp8Vh8USbjoMbmDPbjH1b4Ccg6NZ0pg1cXhBIzb69+zj++ONZtGgRGzduBCCSIboSQgXwEqEEaAmBgFCivCZUIQBXXnkl27dvZ2hoiK1bt5Y7SyFo2BpBLSRrZhRZQfcHpuhcXKE1GhM1ImQ1GGzMmXvO/BPWPveS7fS849Y88sxVgxfEz1lf7QrI2hmdbwvpOadJnrWJRxMCqVlg5jI3KM9on3rqKW644QbSNAVgWdeR9Na7sYGHCviagLqAmsRGnkqtyrKZR07vHw39/f1s2bIFgBlRD2/1C9BWkUwkpM02XWc26VkVkLdyKp2KfNCz7VtDF88/Ye0dB3C/cIL8HT6zPN1mr2veXXTaMUn1kBBZdVQXCMK3FLS2WZIxS4es00GNu5IHebHVVZWLjjyfvu4+rCyzjggEBOCD6ZyuHPOrs7ljz2baJn5J/3N7zuKdagVpUqBqBX0fyun6dYm3HtMUDP9Hwp6rJ3n+8dZJZ/CuR/6Tu7e9hMDvcMI5VTrOFkYytSNj/K42yZ4CV3jCGZ7uVRJnPc3BgkP8fA7WsxkshpFCsrB2MB9ffC5Hz15KRgHa4xU4Dahy8TocuSvornWxrPtw9reHKUxBX9DLhzt/m1Oi4zHa0P12mLvOISsFU08UDN0Ys++aJhNbM0SuCAgCj526nttvnK6zpV3L55ZX6fhJQFR3WCyGggKvHL0nVpl3QkhlhifeHzCysUJ9og8xWzEVT+HGCoy2JJ0F1AUq0ChVvi4KXVZXJ0siPvNUxjV6SkCHpF6vIwY8zXCImWsS6gcVFJOw/x7LSH+MTyAgRKFRKAwFCc3TP8Dnf/SSCHyfO4bez+rdAZXTNZEEEEIw7+MzmLemis9jXDNGRRnhtnl0LJpP38kHM3vZPGrU0M869C6PmPSkNiUmJjUpWZ6SZSmMWyrPKBpPB3S0qsw6eh4HnXwY3UtnIqxCj+dES/fikgyvoGtFB7WVXST3G1SuCYgAyGj/9fv53AvfGV5yKnEWn70mo30qMBxRp3NhD7OO60QW4JXGRtFYLqO7i1SNORx0SdSCCL2wguzShJmmc6DKnK1d8cyHG6Nyu03YYeKe+yrjs+6utTq2BeimRHZogsOqqEMi6NF46bCZbOaycpeLokGnAkQhmHF0je7lvUTUkagkIz7/TP7y8y/G/IrvA2fw5/0Z7XdazM1iOKAY8jjlcEFwtZ87c8nSiy461o/KS4r9CcmTTeLHJkkeb5IPpTjrcMIZ4OxGq7Lw4J19Ry14tm9Zx0R1kfDiJCd80zuHGcmIn5gkfmyC5MlJ8oEYO8I3jvr0havd3JmLXSW6xAuHaXkYCPD4RzJaq0/nU998Od7XPFq8icukIvpYY2X172b8MQNyVn3J4lPPzgAePuimLj0n2BLMjg7FQvL0JPlAeuDNaiewdBXr4pePuZlrH0awQmhJMDuiuqQLGUqK4fT5YqBYsXLvKbsO+P739/7tlol/9SdO9qd/Y8i+cAofT14Np34tAqdwoQOuWP/w1282lwUXVw+XRwP3A6zce8rk1t7+f873JF+0zYJiKMMX7sVjviKym7lWAhoP3jjMSE7ydBPdFYAQ17wY/Oa1Vx86+o18d/P27DfWcsHm18LIqz3o5baWC7a3tqa/P3TdWHgDl9YPtAshrneZje1U8VPw5eb93lWsa718nFWsc8ALBcgbh5syuNQBXHug/Uf8rR5bPzF/4vb2hT8LPPwcn5hezbYuv/mhYiRbaUYzfOHGgX8HPruKdROv5r+ZayvAxcB5IpBzdG9I0BftEpFcsvzB975Ccq/HXlNCP8seffuGk1ziHNb9I4L/Ah5exbrJ/63PKtalwMWbufZLwHKsP91bf6LwnAZ87xfF8qa9ab+E/Q8AqAOb7PPZEAAAAABJRU5ErkJggg=="));

    CreatureInfo info_2;
    info_2.m_id = 2;
    info_2.m_name = "Nose";
    info_2.m_health = 4;
    info_2.m_actual_health = 4;
    info_2.m_shield = 4;
    info_2.m_actual_shield = 4;
    info_2.m_attack = 4;
    info_2.m_point_of_move = 5;
    info_2.m_actual_move = 5;
    info_2.m_enemy = true;
    info_2.m_texture = QByteArray(QByteArray::fromBase64("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"));

    CreatureInfo info_3;
    info_3.m_id = 3;
    info_3.m_name = "Smile";
    info_3.m_health = 6;
    info_3.m_actual_health = 6;
    info_3.m_shield = 6;
    info_3.m_actual_shield = 6;
    info_3.m_attack = 6;
    info_3.m_point_of_move = 2;
    info_3.m_actual_move = 2;
    info_3.m_enemy = true;
    info_3.m_texture = QByteArray(QByteArray::fromBase64("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"));


    CreatureInfo info_4;
    info_4.m_id = 4;
    info_4.m_name = "Octo";
    info_4.m_health = 2;
    info_4.m_actual_health = 2;
    info_4.m_shield = 2;
    info_4.m_actual_shield = 2;
    info_4.m_attack = 2;
    info_4.m_point_of_move = 15;
    info_4.m_actual_move = 15;
    info_4.m_enemy = false;
    info_4.m_move_type = MovingCreatureType_e::fly;
    info_4.m_texture = QByteArray(QByteArray::fromBase64("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"));

    CreatureInfo info_5;
    info_5.m_id = 5;
    info_5.m_name = "Nose";
    info_5.m_health = 4;
    info_5.m_actual_health = 4;
    info_5.m_shield = 4;
    info_5.m_actual_shield = 4;
    info_5.m_attack = 4;
    info_5.m_point_of_move = 5;
    info_5.m_actual_move = 5;
    info_5.m_enemy = false;
    info_5.m_texture = QByteArray(QByteArray::fromBase64("iVBORw0KGgoAAAANSUhEUgAAADAAAAAwCAYAAABXAvmHAAAACXBIWXMAAA9hAAAPYQGoP6dpAAAAJXRFWHRjcmVhdGUtZGF0ZQAyMDA4LTA4LTI0VDAwOjI2OjExLTA1OjAw7PaYmAAAACV0RVh0bW9kaWZ5LWRhdGUAMjAwOC0wOC0yMFQxNDoyODowNC0wNTowMLqbNkEAAA5cSURBVGiB3ZpbkGVXWcd/31p777PPOX3vnslcejpzSWYYYEKCEAiGi0VUKEspoZTCC2VpWWWVClWWL+qLaJXAm2AJglIKT0CJghcwCGUSSEhMMMGEmWFmMjPdPdM9fTnTl9Pn7Mu6+bBP3yY9YzqEB11Vq/fZ++y19/+/vsv6r+80/B9v8nI/8DNfCOsf68Ae4ACwH7gNGAyBGPDACjAFnBdhMgQyEfiN9+4O0stCYAvoEeD1wFt7x6PAGNAQIVIKdK+LgPMYa1lwnqdD4B9E+OcAC8KLJ/JDEdgCfC/wXuCXgVNAY9tLBOII0gRqvZ7EEGmwDtpdWGljS8MTwJ8BDwLuxZB4yQR64AV4G/AnwH2AvumLpPcyqT5rBVGPVL1W3bPchm5GK8CHgL8CzP9G4iUR+MwXAkqB97wb+Dhw8MWODWHbWQVCKoskMZQlFIY14PfLMv90HNfCb77vpvOyewJf/U5g5nIgEF4vIl8EDt8MYdg+FAFEgRJQqjoPvSHeB3yoyHgHAWYI4RcQHkuiiF/7xZ2hRrslMH3RAqQi/F4IcvgFMMP2K0LlKo260FeHeirEkSBS3ecdWA/GQFFClgeywmNsOBA8H/Qh/JdzLr8Znl0TCMEDnAqBn9wZ+Cb8OBJGBoXbxjQDTQGEvIS8qMCWFpyvhogIcQxxHGjUhXbH0em6B4L3rwH1xM3w3Ny5dmh/+dluj0R4T9U9wQdC2N4JgUYKtx/Q3H4gItaK1oowMw/XWtBahpU1WOtCN4NuDp0MshyKUggItUQhhLq15vmxvc1vH7/jbr710BdegGlXFvDeo0QIIZzYev1Gl2k2FUfGIwb6IuZasLAEWQHe3/r5LlQWKQ1EWoh0RBSZ+05/74l0YPjojm60KwLBexwoYGw9Am8M2bSmGL8tolaLmJqFpTZYW30rVEG67ZmhCmilHNZ4nBeiKMI6cE5wTt82OHw0VUr98AR8NYUKSBpNR1EIzshGLlNKGB3SpGnE7AK0lj1F0WWwPzDYn+B8zOqaojS9dUHg0IHA0UOeRt3T7Rp+cGGVsxcszf69RFGMdcGKrjlRO3v7Lgk4AgQB630BISKpKYq8msl6GjHYH7PUFmbmOqytXOEt9w1y8vgQ9VTjfGChZXnmjGLxuuL4EcvdJx1JAgRBjSZMHBxlqH+Wr37z+xwYfwUhBOO993Kj6XpN7YaA854QvHfeZ2ttjdKBsTGD0h4fPM26wgfN/GLO5YvP8bY31Xnd3aM06oq1tTWy7iq3jRle9+qC8X2GOyYywHD16jz/9vVHKIoSaw333LWHI4c8U5PPE4I3Al7JzlB3RSB4h7U2eO+6zgVCcDhnCMEiBJJY082Fyalp9u3xnDw+QlEUWGt5+JHHefTRpzDG0UgLTh7roKSgLA0zM7M8/PCjFEV17pzl+B3DrLZbdLsdm6YN78POGWDXMRBCIIi0CVAWjk7HYoyimiEhyz2rqyucONIkeEtpA1orJienSJIYYwzGGGLtsdYTQkSeZ3Q6bYqiQGuN1goRUFowpjRJkvi8yF4+AsAyVHnbGI21gTh2GBvwQJREZIWnKEp8CGitESwEoSwrN7m+kpAmlnpakNRiDhwYxVqLcw6lhKmZLrW0SRTF5epq24dwozCp2q5c6A8/OI73Hu/9Eni0DhQlOOew1mGMBxQjI3u4MmeYW8yw1lAUBUeOHGJi4gBlWdDNHM9P93NlrkmWlewZHead73gAaw3WlDw/1eXClGPPnv1EOjKt1lx4obJ6CRaAXiYKLCeJ+IFBpebnHWlN4ZzHOY+OA2Mje5lbLHjsmS73nkrobwROnjyO97DStkzNjlC6Oj5OOTepGB1cpZbUmGs55q4Lz09rBgYmqMV12qsr5eTli6F/YPDlIuAJgaWiwCwvuZpWwvihiLlrFusccQCtY/btuZ1Ovsrjz2bsHfEMNAWtanTLPoJOOXwY0rpwpRjkwtV+wGKsoyiFvkZMpDR5keO9Kz/7yZ8KH/mLmZdGQEQQEVGq8rZ3vOtY+PLnn1n1SaMsS6mlqRC8JQSHtZuZQilNf2OYEIawIVDrF+p1YSQGrdnQ0ocOwdiYUJQRkU5YmIfFxZ7MrtzVfOJzXbTeeSHbiIEoitBakyQJSZJIkiQqSRIdVy3RWqda68Z9J6Q5c/U5Ay4fGdEY67h+vaDbNTjnuDHY6nXh2DFFWnecv3SdS9OrOBd6ChQgMD27wunz83TzLocmoF6vxoYQ8MGbxYU5klq6swVqtRree3ornYiIolKp0ZYeAwkQiaDPnf5G/8FDp0pREdY4Zq9VSqfZ2E4gBKg3IE1hcjrj4uQy9TRi356UtBZjDGjtmF/o0LqeMzQQMzxYQylFCIIPAe+8lUpA7kwgSRLyPEdE9Baw6z3ZcqwBSaR1vDh3rr/Is3J+TuNdqISagN3BAqYM5LlncCDi0P4GjXqEEJieDrRXhQMHA0cn+hgditkzmjA/58kyXW14vMc5Wyqt13XYCwm0222SJFE9oOkNoG/sNVEqabfna2WZFTpqsDW9GWOx1m5IThFot2F2xjE0FDh2eADv4Nqs0GoJIcDkZc3gYJ2+eo2llmJ1NdqQ3esuJD2FuiOB9Rt7rpNQFaReAHzzKLUiW62VZWbSul/foQFgewREbRVewswMtFqKOA4YK+SZIGIREcoS5uY0qqc2Bb8xAb7aMJUuOBqNvpsTcM4FEXEiEnpAG9tBbxxrIpIYk9eLvGN9/1aXCRhbyQStZR07IDhX7XkJQl/Tc2TcMDzgSRIIQVhdU1yajujm0iu/VBLdOYv3zohSOGdvTsB7H7z3VmudA5bKhRpsulRtS0+cM7Wy7DjvPWGLb1prMdYStizw62ACwoG9cO9rPEMD1d4BJUgIiBIGBzyPfTfgLBsWcM7hvTfSe/ZNCYgI1loHZFrrVaAPGN5CYgM8UAvBJWXRZSuBQC8GjEHWCcjGH5JguHvCMRYFwhoQAm5xkdqJExTPPcfBkQM00gGWVqptK7KhvVxw7tYWCD3BZa11ItJWSrWAfmDoBhJVIItKRHTDb8k6gYBzDmMssuHPFfggiubqDOpLX2M5AbeyijeW8vJlmvffz9qTT+H3TWBP/DpOj+IJCOCdA4JzzuGcuzmBdXMppYIxxsRxfF0plWy1RAghDcHFwbv48B1vPdQ/eHDc+e1p01mLtWZz1ZSKQhAhl5iF756huXIFFxRl1CCvD2P+4zRR7ugUOSu3K1xqkN4G2pgSYwzee+557fCtCcDGnjcYY4o4jueVUjXvXb/AcL05OjQ0cnh0/PZ7Jw7f8ZZTSdI3sDkrYWMSrLXoyPbmfjOY15IBnnn1LzE8d5qsbw/tkSPkzTG8TtA2J6gIG6Vg7UbFrixL8iybeM099/M3n/rSjgRuVVrUwPCRO998/4lXvvO3BobGT9Xrw0NxUq8jSsKNO6QAcRwzNDxGrVbbZoGNVym1cR2oAnjr+UbtonLr5eUWy8vXr5gy/4gpu4/m+cr03MxzS/2D+/3X/+kPXmiBG1oMjBw7/sDbD0684acrLw89K20G7lYCVZ3Tbwm4zQWtyovr+LfM2zaSm+fGGLJuB+fcuFLRx5K0fzmu9V3u69/3jTxb/sTHPxemPvB+uSWBCBi+dOGRtf7Bg5cbzdG9SkWJiJJAIHjvlVJKpHJ4UQqtI0IIvZQnN9SAtp73SjEhrMceSms27RDodtbI83w9y2lgVJBRRN0d4OLv/iqf/sD7b+1CMdXPQ8f7B/YdHt1z5/5Gc7Q/itPI2ZJup1UbP/zG1x4+9uZ7lY6kltRoNPuIorjSMYGeOvVoHW2Tw+sWMGVJp9MmTmo0Gk3WJXtRFCwtzeVLrSvT3jvbs1Hw3q7l2coTV6ee/OSZZ7/8A8DfygIWmAFW2qvXvt9evbaukdL94/fcefT4A+/eu+9VR3QUS5rWSZIaQpWJnLeURUFRFFW5pdlHmta3uI7gnGVtrU2WddF5hjElcRTjnCPLu3Q7a3Zh7txT58989cHl1qV5pWNvbdF2tpgB5ul58Iv9fUCoXGrg3vt/5x0TR9/0R3HSfEUcJ9KoN4jipKrr+4A1JXmRY0xZyXSg2TdAs9Gs/FsE7z3dTtsuLkxOFkUnazRGx5Nac2hdNm9RntaU3adbixf+9OEH//ih3qQaqmgKsLvqtAb2n7zrPb/d17//rcEHUSKs65SyLMjzjCzrUuSZMWXWCQElIlorTRRF1WJnHVnWYfbq6X995N8//OGzz33lwU577my9MTYYJ337Qwhqs9LtlVLxwbQ+fOfA4PhXHnzm8dYnPvqhbelvN3viAJgrk49/J60P35XUmvut1VGedwLBF9aVbVN2r2XdpXNLrYvfn599tn3w9jf8xKHDP/7zRZEpUYJSCmNKOu2lCxfOfP1jK0tTTwFcfv6hM62Fc6dP/divvG/vvlf/nI7Sgc1XCt67UevKgVftsJbthoAD5s8++49fXpw7872RsTsPRHGaBoIxRafdWZu/vrI0udDtLC4BGTBYb47W94+//mdCIDWmBBG8c3apdfnvzp3+l/8EOlQ5udNenVl54lsfu3L8lT/75MGJN76r3hh5paio7r1ZWF2e/tT3nvzbKyKfXF/jXrIFMmBqcf7szOL82S1bc3yP4OYiATSae0REdLU2VNeKfPWhC2e/9nmgu+VeCyw7W2Rn/vvvZy6d/8Y39+6/a7zeGKl3O4uzs9NPnre2WLsR/G4JrJOwvX6rJkBI06FUUNH6JWu6p2evPPXR6UvfnmZjWdv27Bwo8mx5eeriIxd6118wMT8MgRfbAlCYsnPeuvKKEpWW5dqT164+/edPP/HXj1FlkluNfTGTBPwI/ldiS9ONvr1DR+58+wkRpa9dffri4tzpBSrwO5cYXkL7URLY6fkvG/D/N+1/AE5V0XkMsvHJAAAAAElFTkSuQmCC"));

    CreatureInfo info_6;
    info_6.m_id = 6;
    info_6.m_name = "Smile";
    info_6.m_health = 6;
    info_6.m_actual_health = 6;
    info_6.m_shield = 6;
    info_6.m_actual_shield = 6;
    info_6.m_attack = 6;
    info_6.m_point_of_move = 2;
    info_6.m_actual_move = 2;
    info_6.m_enemy = false;
    info_6.m_texture = QByteArray(QByteArray::fromBase64("iVBORw0KGgoAAAANSUhEUgAAADAAAAAwCAYAAABXAvmHAAAACXBIWXMAAA9hAAAPYQGoP6dpAAAM0ElEQVRoge2Zaaxd1XXHf2uf6c5v8PPzEDvGNoNdUhMwLSnQDBSV0lIhglCLkqhN0+YLCerwBTVfqkoRQqloOkoliISkShTSJiEpTVSqRqGtoLiliYMJGMexjXl+83333fmcvffqh3Pv4/nh56kmUqUu3atz7z3n7PP/r7X2mi78Hxd5KxZN7/9wVUSuEWE/InsF2YnoVlEmgCKCF9UlVI8h8j2MeRqR78iffKZ3oc+6pAQ69/3GzQa5V0RuQ9gpggHJX2GIFItQKiHFIhLH4By0W1CvI1n6gor5tHn40S/8xAk0P/qhnxMjDwj8CiKBAIiygl8U4iQHniRIkuREymUoFBBn4dQpdGYGnP0y8Pvhpx+b+okQWPrIB37XiDwIFEQAyZfMD5IfBURBAUEH5wUxAlGEqdVgbAyxFp0+BVn2AnBX/OefPfGWElj4zXvvNyJ/NlxJhu4ygCoyQD4konraQ/PfBtcbg1QqSBhCuw3ovwG3Ff7yc52zYQgvFvzsB3/tOnX+Qbda4yqIGaIDweefVZHBPjBxDIUEiSIkDHICqmia4vs96PXAeYCbReTjwENnw3FRFpi+9x4BfUowtyOs8fdVi6uCEcJalWjrFsItmwlGazl4AGvBZpBZNEvRbg+/3MQuLOIay6izCyFyTemRL7y+HpaLsoBz/nLgF0RyDeeg/Yq/o4B6wlKRwlVXkOy7mnBsFLpdWFyA2YXcTfr9nIR6JAggjAiKCeG2LdhqmezU7IaZTuf9wF9cWgLWXy9CjMgbJpSBn6OIQrRhjMq7rie+fCfSbsH3/xtmZqDTHoDO9wOqAz8YmM8ESLFAVCoRTm4gnbK3PPrB9//Vb//tV/0lI+C925H7e65uETMAoqBKMrmB2ntvIp4YgxcPwokT0OuuED3j8Q3tQKsFnQ5SLLGhkFxzZdavAo1LRsA5HYWBjzPYrELuNuUS1ev2EVeK8MJ/wcx0fpMx6y13ugwJqUKnTSHLRq6vleP1Lr9YFwplGH1WHppHmtLuHRQmRuHQizl4kTdr+XxFAeuyQhLa9S65OBdyPhtmJxnuXPXEtQql7VuQ6VMwN/u/Aw8oildSBXdJCTin3aHGh4lLvSceHyUSzTXv/fm7zWmIwpy0d2AdqmphkL4vHQHfWQkcg7gpRohqFYJ2M09GUZQT8G6YmM4uxkCpDNURrAiht+jcHN51M1TXtcBFqAic9S3nHM56nPM461CEIBTodiApwORmmNwCE5M5mXNJHNMd3cDDx6b5pS//A984fgoZHUchA9bVwEUR8M41nVO815yAV5xTfD8FhWx8A5+drnP3k0/zrZOzMDp+bncqFnl+bpEnDv6Qfz98hE98/VukEkAQWhcE6952cRbwvuGc4qzHO4dzis0crtuHOOZ79RaPHjjIPx48xB9+49vYKIZwfRCDRdkYhUy9ephevc6NV+wiFHDOZ+ZSb+KimkbLOS+CyaOQRxVsmoHzjISG46+8TG9xgb1X7cYI4Nfdh7m02/zUxEae/PCvc2ypwe2XX4bOzeF6aSo+WdeFLorAgcbS0k+XqzZTjYelA4HDpQ7tdLiyWuWJD93DS7Pz3LX3ckxzOe++zibOwuI811YqXDu6BRoL9FstvHeXPgp98vjhxqNX7MtiY2I/LGUUsjRDrUUW57lxpMaNG3dDq5lvbD2HBQRwGdnsAmmmJIlBvEe9psHDj164BcIwFMn9wxhjDGBU1VjU1kVtz/t+LKasqnnxaRWXZqj6vERuLK7qXCD3I85ARMBA1rOcPLbMzFQbaz2FcsK2HWWMYd0sfEYCcRwbEQmAYHA+BCIgEpEoAGPRWsu55kgQjq++12cuN7YR2o2U9nIPlzmMQBga4sQQF0LCKMAYQb3S72UszfeYa4fotp1M3LADExiWDx3h1PEjTG4Mzo9AkiQyADoEHK86rn5H1mup4bL22ylgV7mndw5rPccP15ldyCju2kGybROmEOebuN9Hux2CThtJe/ggwo+MUbj1Sna8+2ep7dmNDwKa3Q4Ty22O3vcJ0s5Udk4CQRAMwReAZKjxM4BPQCKHJk3nesOedijqlZNHFqmbUfb+6X3Ee3aTVCsrsVoBn1lcmuGtxauSVMtIEFBvNKg3m3jnKI3U6JcK+CTGt/15u1AwAD8kEQ6Oq8CTCERWNWyp68majjTrZ3QX6kx+9E4KP3MNjfl5+t5RqVTo93r00xQxhlKpRMf2sc7SbymZzSiWSmSqJGERna+z+MVvIq+dIJ6Iz03AOUcQBG5QIidAcRXwwmoCQORQaTmbrc2C3jokiFl47gVKd7yPDVs202i3WFhaIooiCpUyaZax0FymXKlQjhN6rSZhCu71WfovH2H+wEHqzxwgbC2xZVcFm9lzuxCg1lobRVGfPOvFQHkN8HhggQRV33Pev6lSViWpxjRffJXX7/9jWrfeRHHvboLxUSSO6Pb6uOU2vr5Eo95gbnaB7NQs/RNT9F+fwS630MwyvrXKjv2TpP2MpcX0/FzIe++zLOtEURQDtQHgymrwK59VfVudrsXvrWOkFmAqFbRWYuGJb2KbnbxhH5TIah2aWXyaoZlDjSGIQ+JixMjmMmMbC4xsSDBG6LY9nKWMOI3AgIS11i6HYZgMSIwPLJFwmiXE+TOEYGs9USxsCno0bJvk2r10jp2i86OT+IH/ixGMMYSVIkkxoFAOKVVCKrWIMDIYQ15jIagqxshZa/E3gXDOpSKyEARBERhZRSJWiK36ECG4qlB+m12Tk1SVLHMUSzGj2SL943OEzlDamiAaEwRCGBui2BAlAUEgmHySimoO3KGDCYdgrQe9wESWa9L2gVNBEBSAaqZa9TnwZDSIaneOTl57U2VkV8+vtm6uMWcdNvOAkJQiEgMiIW9EXB2+GJbk+fBxcG7VpM9ZR7+fJRdMgHxTd1T1NYwpb4mSq/aXa++6uljZvr9U27Y9LtQyVfQMNZb3ivMub0HW7nJR5LT6YvUlq8CT99o+c7w2vfSebXHhspNp79iZgJ6t4w6A6jvKtbsf2rHn4ckorhmEVD1W3wxdFcLIsPltYxTLb1ba6Vzk9O9y2pnBiEaZn2myNNdkLkunDraX/+XlbuvA882lfz7Sa7+0GuR6EgOX7SqU7rhnYuvPx5JXVSIQihCJIRDBrSrO4kJEpVrAGMldQ/NBl6qi6lEV8p8U9at+94Bn5RyqpH1LY6FFmjpqYVjdW6rsu7k2fvud45s+0nSudajT/A84ezntAfd8a+nA7/340OduqIzu2RjHYwUJI0W16Wy/GoTV/ZWR7ZAXa6VyDCI4OwgconnxuTKC9CtTxHwSo3Q7KUFgKJTiFWN4rywvdbE9R2QEQci84vGk6qXt7BsTzbMQgDz6TAKj5DmhOLCaB7bdMbbprge27/7lOImkWEkolGKCQe/rvafXS8lST6EYkRQiZJXfiECvk7K00CYIDaPjZcIkBK/02ikzi83skZPHnnqt3z2amKAQgOl413i11/7P6bT/HaAO+POZOpkB6IDcrWo31cbv/sDGrb91TWX0HcVSbIqVhCAyCIMSObV0233SXob3SnWkSHWktKIyAbz1dOpd2p0+cWDwocFEBvW5+3jn9VCn+crfL0x/6emluceBHmAHx2HFoOfotIFBETm4oXDLyMTvfGrn3k9ti4ubTBxIsZIgRvCDxr7X7tNr9pHMg+Y3hlFIFIV51FJFnWep0fV/fezI1766MP30nE3TXVHx7caq9NIMn0dh2Z4UJ24b2/i+ySiZeLa59HceXWbNmOV8CKy2xOh11ZF7bhudvNaqkrdpglqP9BxZJ6Xdy5jp95ZeaDcOp6qyIYrLGCGK8kc559Gu5W+O/eiLj0yfeODH/c6/PtusP/dKt13fV65dvSlOCm4Q5awqDthTrOx7tlX/7kzWP7oW1IX0xAr0nlqc+Xwkwv7y6L6SMRUF13RueTbrT5/sd48f7XdePtJrH2pY29kaF255/Ip3frKcStRudjGBIXDKDxvLxx+ffu1B4Phg7YVnm/Wpjx198Qf3bbnsY7eOTtwQieTltRim0t7yYpYungnUhU5eDflGLgNjJi8vvEIXWAba5CZ2QKkcBL/4lav2f2kkjBKneRIrGMMfnTj8wFP1mbX/fQWDdXe+uzb+q+8dmXjP5jjZNJ+l01+Zn/rMDzrNJ4F0LaALnUr4AcgOMLeqyjrTyMFujpKRxATR8GTFGP6pMf/dby/NPnaG6x25El56ZnnxyDPLi48ZoeSVBrDIOuPFi/2X8hwzkhxQOQijUmBMgCExhuea9e8/dPLIx53q3Fnuywbv9rlmYXBhm/iCpafe7i6U35mp7399cfprD08d/YO6zQ69lc+8lCJAJDAZi9lOnkP+X9bK/wDrs0uV2ZqR8AAAAABJRU5ErkJggg=="));


    m_map_of_pawn.insert(std::make_pair(0, 0), new Pawn(info));
    m_map_of_pawn.insert(std::make_pair(0, 1), new Pawn(info_2));
    m_map_of_pawn.insert(std::make_pair(1, 0), new Pawn(info_3));

    m_map_of_pawn.insert(std::make_pair(8, 0), new Pawn(info_4));
    m_map_of_pawn.insert(std::make_pair(6, 1), new Pawn(info_5));
    m_map_of_pawn.insert(std::make_pair(7, 2), new Pawn(info_6));

    QMap<std::pair<int, int>, CreatureInfo> map_of_creature_info;
    for(auto it = m_map_of_pawn.begin(); it != m_map_of_pawn.end(); ++it)
    {
        map_of_creature_info.insert(it.key(), it.value()->getInfo());
    }

    emit initializationPawns(map_of_creature_info);

    Update(m_position_map, m_size_cell);
}

void MapOfPawn::selectedCell(int x, int y, bool mark)
{
    if(true == m_do_something)
    {
        return;
    }

    Pawn* selected_pawn = m_map_of_pawn.value(std::make_pair(x, y), nullptr);
    if(true == mark)
    {
        if(nullptr == selected_pawn)
        {
            if(m_selected_pawn.first != -1 && m_selected_pawn.second != -1)
            {
                m_selected_cell = std::make_pair(x, y);
                m_selected_enemy_pawn = std::make_pair(-1, -1);

                emit selectNotPawn(true);

                //BEGIN WORK
                m_do_something = true;
                emit setNewPositionPawn(m_selected_pawn.first, m_selected_pawn.second, m_selected_cell.first, m_selected_cell.second);
            }
        }
        else
        {
            if(true == selected_pawn->getInfo().m_enemy && m_selected_pawn.first != -1 && m_selected_pawn.second != -1)
            {
                m_selected_cell = std::make_pair(-1, -1);
                m_selected_enemy_pawn = std::make_pair(x, y);

                //BEGIN WORK
                m_do_something = true;
                emit setNewPositionPawn(m_selected_pawn.first, m_selected_pawn.second, m_selected_enemy_pawn.first, m_selected_enemy_pawn.second);
            }

            if(false == selected_pawn->getInfo().m_enemy)
            {
                m_selected_pawn = std::make_pair(x, y);
                m_selected_cell = std::make_pair(-1, -1);
                m_selected_enemy_pawn = std::make_pair(-1, -1);
                emit selectPawn(selected_pawn->getInfo(), true);
            }
        }
    }
    else
    {
        if(nullptr != selected_pawn)
        {
            emit selectPawn(selected_pawn->getInfo(), false);
        }
        else
        {
            emit selectNotPawn(false);
        }
    }
}

void MapOfPawn::selectedNotCell()
{
    endWork();

    emit selectNotPawn(true);
}

void MapOfPawn::Initialization(QVector2D position, QVector2D size)
{
    loadPawnsFromServer();

    m_position_map = position;
    m_size_cell = size;

    //TODO: przenieść gdy komunikacja bedzie gotowa
    receiveFromServer(QString());
}

void MapOfPawn::Update(QVector2D position, QVector2D size)
{
    m_position_map = position;
    m_size_cell = size;

    for(std::pair<int, int> key : m_map_of_pawn.keys())
    {
        Pawn* selected_pawn = m_map_of_pawn.value(key, nullptr);
        if(nullptr == selected_pawn)
        {
            //pionek nie istnieje
            continue;
        }

        selected_pawn->setPosition(m_position_map.x() + (key.first * m_size_cell.x()), m_position_map.y()+ (key.second * m_size_cell.y()));
        selected_pawn->setSize(m_size_cell.x(), m_size_cell.y());
    }
}

void MapOfPawn::endWork()
{
    m_do_something = false;

    m_selected_pawn = std::make_pair(-1, -1);
    m_selected_cell = std::make_pair(-1, -1);
    m_selected_enemy_pawn = std::make_pair(-1, -1);
}


void MapOfPawn::updatePawnInfo(std::pair<int, int> position, CreatureInfo info)
{
    Pawn* pawn = m_map_of_pawn.value(position, nullptr);
    if(nullptr == pawn)
    {
        return;
    }

    pawn->setInfo(info);
}


