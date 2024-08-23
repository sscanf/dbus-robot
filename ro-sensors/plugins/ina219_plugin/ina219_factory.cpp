#include <QtPlugin>
#include "ina219_worker.h"
#include "ina219_factory.h"
#include "ina219_worker_interface.h"

ina219_factory::ina219_factory() {}

ina219_factory::~ina219_factory() {
    release();
}

int ina219_factory::init(const QString &strName, const QString &strDescription, bool bEnabled) {
    Q_UNUSED(bEnabled);

    ina219Worker *manager = new ina219Worker(strName, strDescription);
    m_listAllObjects << manager->getAddress();
    m_listManagers.append(manager);
    return EXIT_SUCCESS;
}

void ina219_factory::release() {
    foreach (ina219Worker *pObject, m_listManagers)
        delete pObject;
}
