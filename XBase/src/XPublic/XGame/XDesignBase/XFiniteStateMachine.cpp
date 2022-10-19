#include "XFiniteStateMachine.h"

#include "iostream"
#include "XLog.h"

using namespace XDESIGNPATTERBASE;
using namespace std;


void XIState::onEnter(XIStatePtr prev) {
    //XLOG_DEBUG("%s::default OnEnter", m_str_name.c_str());
    //cout << "State::onEnter" << endl;
}


void XIState::onExit(XIStatePtr next) {
    //XLOG_DEBUG("%s::default OnExit", m_str_name.c_str());
    //cout << "State::onExit" << endl;
}

bool XIState::update()
{
    bool _b_res = false;
    for (list<XITransitionPtr>::iterator iter = m_listPtr_transition.begin(); iter != m_listPtr_transition.end(); iter ++)
    {
        if ( (*iter)->onCheck() )
        {
            if ( (*iter)->onCompleteCallBack() )
            {
                doTransition(*iter);
                _b_res = true;
                break;
            }
            else
            {
                doTransition(*iter);
                break;
            }
        }
    }
    
    return _b_res;
}

void XIState::onUpdate(float deltaTime) {
    //XLOG_DEBUG("%s::default onUpdate", m_str_name.c_str());
    
}


void XIState::addTransition(XITransitionPtr transition) {
    if (m_listPtr_transition.size() == 0)
    {
        m_listPtr_transition.push_back(transition);
    }
    else
    {
        int _i_order = transition->getOrder();
        auto _iter_transition = m_listPtr_transition.begin();
        for (auto _transition : m_listPtr_transition)
        {
            if (_i_order < _transition->getOrder())
            {
                break;
            }
            _iter_transition++;
        }
        m_listPtr_transition.insert(_iter_transition, transition);
    }
}


void XIState::setStateMachine(XIFSMPtr stateMachine) {
    m_FSMBase_parent_ptr = stateMachine;
}


void XIState::doTransition(XITransitionPtr transition) {
    transition->getFromState()->onExit(transition->getToState());
    m_FSMBase_parent_ptr->setCurState(transition->getToState());
    transition->getToState()->onEnter(transition->getFromState());
}



bool XITransition::onCheck() {
    //XLOG_DEBUG("%s::default onCheck", m_str_name.c_str());
    return true;
}


bool XITransition::onCompleteCallBack() {
    //XLOG_DEBUG("%s::default OnCompleteCallBack", m_str_name.c_str());
    return false;
}



void XIFSMBase::addState(XIStatePtr state) {
    state->setParent(shared_from_this());
    m_mapStrStatePtr_states[state->getName()] = state;
    if (state->getTag() != -1)
    {
        m_mapIntStatePtr_states[state->getTag()] = state;
    }
}


void XIFSMBase::removeState(XIStatePtr state) {
    if (state->getTag() != -1)
    {
        m_mapIntStatePtr_states.erase(state->getTag());
    }
    m_mapStrStatePtr_states.erase(state->getName());
}


XIStatePtr XIFSMBase::getStateWithTag(int tag) {
    return m_mapIntStatePtr_states[tag];
}


XIStatePtr XIFSMBase::getStateWithName(string name) {
    return m_mapStrStatePtr_states[name];
}


void XIFSMBase::onUpdate(float deltaTime) {
    while (m_state_curState_ptr->update());
    m_state_curState_ptr->onUpdate(deltaTime);
}
