#ifndef BASETOOL_H
#define BASETOOL_H

#include <QObject>
#include <QPoint>
#include <QPen>
#include <memory>
#include "../smart_ptr.h"

class Canvas;

class BaseTool : public QObject
{
    Q_OBJECT
public:
    explicit BaseTool(QObject *parent = nullptr);
    virtual ~BaseTool() = default;

    virtual void onMousePress(const QPoint &point, Canvas *canvas) = 0;
    virtual void onMouseMove(const QPoint &point, Canvas *canvas) = 0;
    virtual void onMouseRelease(const QPoint &point, Canvas *canvas) = 0;

    void setPen(const QPen &pen);
    const QPen& pen() const;

    template<typename T, typename... Args>
    static smart_ptr<T> create(Args&&... args)
    {
        static_assert(std::is_base_of<BaseTool, T>::value,
                      "T must inherit from BaseTool");
        return smart_ptr<T>::make(std::forward<Args>(args)...);
    }

protected:
    QPen m_pen;
    QPoint m_lastPoint;
};

#endif // BASETOOL_H
