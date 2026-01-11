#ifndef METHODNODEFACTORYHYBRID_H
#define METHODNODEFACTORYHYBRID_H

#include "logic/Node.h"

template<typename T> struct MethodNodeFactoryHybrid;

template<typename Device, typename R, typename... Args>
struct MethodNodeFactoryHybrid<R (Device::*)(Args...)>
{
    static Node::Callback make(R (Device::*method)(Args...),
                               const std::vector<QString> &argNames = {})
    {
        return [method, argNames](const QVariantMap &params, const QHash<QUuid, QVariant> &inputs,
                                  NodeContext &ctx, QHash<QUuid, QVariant> &outputs) -> bool {
            Device *dev = ctx.get<Device>();
            if (!dev) {
                qWarning() << QString("Device not found: %1").arg(typeid(Device).name());
                return false;
            }

            try {
                call(method, argNames, dev, params, inputs, outputs,
                     std::index_sequence_for<Args...> {});
            } catch (const std::exception &e) {
                qWarning() << e.what();
                return false;
            } catch (...) {
                qWarning() << "Method invocation failed (unknown)";
                return false;
            }

            return true;
        };
    }

private:
    template<std::size_t... I>
    static void call(R (Device::*method)(Args...),
                     const std::vector<QString> &argNames,
                     Device *dev,
                     const QVariantMap &params,
                     const QHash<QUuid, QVariant> &inputs,
                     QHash<QUuid, QVariant> &outputs,
                     std::index_sequence<I...>)
    {
        auto getArg = [&](int idx) -> QVariant {
            const QString &name = argNames[idx];

            // 1) поиск среди входов по имени порта
            for (auto it = inputs.begin(); it != inputs.end(); ++it) {
                if (it.key().toString() == name)
                    return it.value();
            }

            // 2) поиск среди GUI параметров
            if (params.contains(name))
                return params[name];

            throw std::runtime_error(QString("Argument not found: %1").arg(name).toStdString());
        };

        if constexpr (std::is_void_v<R>) {
            (dev->*method)(getArg(I).template value<Args>()...);
        } else {
            R r = (dev->*method)(getArg(I).template value<Args>()...);

            // вернуть результат в выходной порт
            outputs.insert(QUuid::createUuid(), QVariant::fromValue(r));
        }
    }
};

#endif // METHODNODEFACTORYHYBRID_H
