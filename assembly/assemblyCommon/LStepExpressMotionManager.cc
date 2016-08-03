#include <QApplication>

#include <nqlogger.h>

#include "LStepExpressMotionManager.h"

LStepExpressMotionManager::LStepExpressMotionManager(LStepExpressModel* model, QObject *parent)
    : QObject(parent),
      model_(model),
      inMotion_(false)
{
    connect(model_, SIGNAL(motionStarted()),
            this, SLOT(motionStarted()));

    connect(model_, SIGNAL(motionFinished()),
            this, SLOT(motionFinished()));

    connect(this, SIGNAL(signalMoveAbsolute(double,double,double,double)),
            model_, SLOT(moveAbsolute(double,double,double,double)));

    connect(this, SIGNAL(signalMoveRelative(double,double,double,double)),
            model_, SLOT(moveRelative(double,double,double,double)));
}

void LStepExpressMotionManager::run()
{
    NQLog("LStepExpressMotionManager", NQLog::Debug) << "run";

    if (inMotion_) return;

    NQLog("LStepExpressMotionManager", NQLog::Debug) << "run in motion";

    if (motions_.empty()) return;

    NQLog("LStepExpressMotionManager", NQLog::Debug) << "run in motion, not empty";

    LStepExpressMotion motion = motions_.dequeue();

    inMotion_ = true;

    if (motion.getMode()==true) {
        NQLog("LStepExpressMotionManager", NQLog::Debug) << "run, move absolute";
        emit signalMoveAbsolute(motion.getX(), motion.getY(), motion.getZ(), motion.getA());
    } else {
            NQLog("LStepExpressMotionManager", NQLog::Debug) << "run, move relative";
        emit signalMoveRelative(motion.getX(), motion.getY(), motion.getZ(), motion.getA());
    }
}

void LStepExpressMotionManager::myMoveToThread(QThread *thread)
{
    model_->moveToThread(thread);
    this->moveToThread(thread);
}

void LStepExpressMotionManager::appendMotion(const LStepExpressMotion& motion)
{
    motions_.enqueue(motion);
    run();
}

void LStepExpressMotionManager::appendMotions(const QQueue<LStepExpressMotion>& motions)
{
    motions_.append(motions);
    run();
}

void LStepExpressMotionManager::moveRelative(std::vector<double> & values)
{
    motions_.enqueue(LStepExpressMotion(values, false));
    run();
}

void LStepExpressMotionManager::moveRelative(double x, double y, double z, double a)
{
    NQLog("LStepExpressMotionManager", NQLog::Debug) << "moveRelative()";
    motions_.enqueue(LStepExpressMotion(x, y, z, a, false));
    run();
}

void LStepExpressMotionManager::moveRelative(unsigned int axis, double value)
{
    NQLog("LStepExpressMotionManager", NQLog::Debug) << "moveRelative()";
    motions_.enqueue(LStepExpressMotion(axis, value, false));
    run();
}

void LStepExpressMotionManager::moveAbsolute(std::vector<double> & values)
{
    NQLog("LStepExpressMotionManager", NQLog::Debug) << "moveAbsolute()";
    motions_.enqueue(LStepExpressMotion(values, true));
    run();
}

void LStepExpressMotionManager::moveAbsolute(double x, double y, double z, double a)
{
    NQLog("LStepExpressMotionManager", NQLog::Debug) << "moveAbsolute()";
    motions_.enqueue(LStepExpressMotion(x, y, z, a, true));
    run();
}

void LStepExpressMotionManager::moveAbsolute(unsigned int axis, double value)
{
  NQLog("LStepExpressMotionManager", NQLog::Debug) << "moveAbsolute()";
    motions_.enqueue(LStepExpressMotion(axis, value, true));
    run();
}

void LStepExpressMotionManager::motionStarted()
{
    NQLog("LStepExpressMotionManager", NQLog::Debug) << "motionStarted()";
    inMotion_ = true;
}

void LStepExpressMotionManager::motionFinished()
{
    NQLog("LStepExpressMotionManager", NQLog::Debug) << "motionFinished()";
    inMotion_ = false;

    this->run();
}
