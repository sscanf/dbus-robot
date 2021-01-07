#include <QtPlugin>
#include "servoscontroller_worker.h"
#include "servoscontroller_factory.h"
#include "servoscontroller_worker_interface.h"

servoscontroller_factory::servoscontroller_factory()
{
}

servoscontroller_factory::~servoscontroller_factory()
{
   release();
}

int servoscontroller_factory::init(Adafruit_PWMServoDriver *pPwm, QString strName, QString strDescription, bool bEnabled)
{
   Q_UNUSED(bEnabled);
   
    servoscontrollerWorker *manager = new  servoscontrollerWorker (pPwm, strName,strDescription);
    m_listAllObjects << manager->getAddress ();
    m_listManagers.append (manager);
    return EXIT_SUCCESS;
}

void servoscontroller_factory::release ()
{
   foreach (servoscontrollerWorker *pObject, m_listManagers)
      delete pObject;
}
