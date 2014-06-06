#ifndef DATUM_H
#define DATUM_H

#include <Python.h>
#include <QObject>
#include <QSet>

class InputHandler;
class Connection;

class Datum : public QObject
{
    Q_OBJECT
public:
    explicit Datum(QString name, QObject* parent=0);
    virtual ~Datum();

    PyObject* getValue() const { return value; }
    bool      getValid() const { return valid; }
    virtual PyTypeObject* getType() const=0;

    bool hasInputValue() const;

    virtual bool canEdit() const;
    Connection* connectionFrom();
    void connectUpstream(Datum* upstream);

signals:
    void changed();
    void disconnectFrom(Datum *me);
public slots:
    void update();
    void onDisconnectRequest(Datum* downstream);

protected:
    virtual PyObject* getCurrentValue() const=0;

    PyObject* value;
    bool valid;

    bool editable;

    InputHandler* input_handler;
};

#endif // DATUM_H
