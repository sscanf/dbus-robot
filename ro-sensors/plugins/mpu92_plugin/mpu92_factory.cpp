#include <QtPlugin>
#include "mpu92_worker.h"
#include "mpu92_factory.h"
#include "mpu92_worker_interface.h"

mpu92_factory::mpu92_factory()
{
}

mpu92_factory::~mpu92_factory()
{
   release();
}

int mpu92_factory::init(QString strName, QString strDescription, bool bEnabled)
{
   Q_UNUSED(bEnabled);
   
    mpu92Worker *manager = new  mpu92Worker (strName,strDescription);
    m_listAllObjects << manager->getAddress ();
    m_listManagers.append (manager);
    return EXIT_SUCCESS;
}

void mpu92_factory::release ()
{
   foreach (mpu92Worker *pObject, m_listManagers)
      delete pObject;
}
