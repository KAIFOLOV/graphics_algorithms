#ifndef METHODNODEFACTORYHYBRID_H
#define METHODNODEFACTORYHYBRID_H

#include "logic/node.h"

template<typename T> struct MethodNodeFactoryHybrid;

template<typename Device, typename R, typename... Args>
struct MethodNodeFactoryHybrid<R (Device::*)(Args...)>
{
    static Node::Callback make(R (Device::*method)(Args...))
    {
        return [method](const QVariantMap &params, const QHash<QUuid, QVariant> &inputs,
                        NodeContext &ctx, QString &error, QHash<QUuid, QVariant> &outputs) -> bool {
            Device *dev = ctx.get<Device>();
            if (!dev) {
                error = QString("Device not found: %1").arg(typeid(Device).name());
                return false;
            }

            QVector<QVariant> orderedInputs = inputs.values().toVector();

            try {
                call(method, dev, params, orderedInputs, outputs,
                     std::index_sequence_for<Args...> {});
            } catch (...) {
                error = "Method invocation failed";
                return false;
            }

            return true;
        };
    }

private:
    template<std::size_t... I>
    static void call(R (Device::*method)(Args...),
                     Device *dev,
                     const QVariantMap &params,
                     const QVector<QVariant> &inputs,
                     QHash<QUuid, QVariant> &outputs,
                     std::index_sequence<I...>)
    {
        auto getArg = [&](int i) -> QVariant {
            if (i < inputs.size())
                return inputs[i];
            return params.value(QString("arg%1").arg(i));
        };

        if constexpr (std::is_void_v<R>) {
            (dev->*method)(getArg(I).template value<Args>()...);
        } else {
            R r = (dev->*method)(getArg(I).template value<Args>()...);
            outputs.insert(QUuid::createUuid(), QVariant::fromValue(r));
        }
    }
};

#endif // METHODNODEFACTORYHYBRID_H
