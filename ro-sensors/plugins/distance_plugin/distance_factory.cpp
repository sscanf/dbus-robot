#include <QtPlugin>
#include "distance_factory.h"

distance_factory::distance_factory() {}

distance_factory::~distance_factory() {
    release();
}

int distance_factory::init(const QString &strName, const QString &strDescription, bool bEnabled) {
    Q_UNUSED(bEnabled);

    distanceWorker *manager = new distanceWorker(strName, strDescription);
    m_listAllObjects << manager->getAddress();
    m_listManagers.append(manager);
    return EXIT_SUCCESS;
}

void distance_factory::release() {
    foreach (distanceWorker *pObject, m_listManagers)
        delete pObject;
}
