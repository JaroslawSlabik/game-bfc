#ifndef I_LOGIC_ARGS_TEMPLATE_H
#define I_LOGIC_ARGS_TEMPLATE_H
#include <QVariant>

class I_LogicArgsTemplate
{
protected:
    QStringList m_arg_list_query;
    QStringList m_arg_list_response;
    int m_count_arg_query;
    int m_count_arg_response;

public:
    virtual bool setArg(const int& name, const QVariant& arg)
    {
        if(name <= 0 ||  name >= m_count_arg_response || name == m_count_arg_query)
            return false;

        if(name > 0 && name < m_count_arg_query)
        {
            m_arg_list_query[name] = arg.toString();
            return true;
        }
        else if(name > m_count_arg_query)
        {
            m_arg_list_response[name - m_count_arg_query] = arg.toString();
            return true;
        }

        return false;
    }

    virtual QVariant getArg(const int& name, bool* was_ok = nullptr)
    {
        if(name <= 0 ||  name >= m_count_arg_response || name == m_count_arg_query)
        {
            if(was_ok != nullptr)
                *was_ok = false;

            return QVariant();
        }

        if(name > 0 && name < m_count_arg_query)
        {
            if(was_ok != nullptr)
                *was_ok = true;

            return m_arg_list_query.at(name);
        }
        else if(name > m_count_arg_query)
        {
            if(was_ok != nullptr)
                *was_ok = true;

            return m_arg_list_response.at(name - m_count_arg_query);
        }

        return false;
    }

    virtual bool setArgsQuery(const QStringList& list_arg)
    {
        if(list_arg.isEmpty())
            return false;

        if(m_arg_list_query.count() != list_arg.count())
            return false;

        if(m_arg_list_query.at(0) != list_arg.at(0))
            return false;

        m_arg_list_query = list_arg;

        return true;
    }

    virtual QStringList getArgsQuery()
    {
        return m_arg_list_query;
    }

    virtual bool setArgsResponse(const QStringList& list_arg)
    {
        if(list_arg.isEmpty())
            return false;

        if(m_arg_list_response.count() != list_arg.count())
            return false;

        if(m_arg_list_response.at(0) != list_arg.at(0))
            return false;

        m_arg_list_response = list_arg;

        return true;
    }

    virtual QStringList getArgsResponse()
    {
        return m_arg_list_response;
    }

    virtual bool setQuery(const QString& query)
    {
        QStringList query_args = query.split(";");
        return setArgsQuery(query_args);
    }

    virtual QString getQuery()
    {
        return m_arg_list_query.join(";");
    }

    virtual bool setResponse(const QString& response)
    {
        QStringList response_args = response.split(";");
        return setArgsResponse(response_args);
    }

    virtual QString getResponse()
    {
        return m_arg_list_response.join(";");
    }

    virtual QString getName()
    {
        return m_arg_list_query.at(0);
    }

    virtual void reserve(QStringList& list, int size)
    {
        if(!list.isEmpty())
            return;

        for(int i = 0; i < size; ++i)
            list.push_back(QString());
    }

    virtual ~I_LogicArgsTemplate() {}
};

#endif // I_LOGIC_ARGS_TEMPLATE_H
