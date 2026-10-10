// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vcounter__pch.h"
#include "verilated_vcd_c.h"

//============================================================
// Constructors

Vcounter::Vcounter(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new Vcounter__Syms(contextp(), _vcname__, this)}
    , m_evalLoop{*this, /*convergeLimit:*/ 10000}
    , clk{vlSymsp->TOP.clk}
    , rst{vlSymsp->TOP.rst}
    , en{vlSymsp->TOP.en}
    , count{vlSymsp->TOP.count}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
    contextp()->traceBaseModelCbAdd(
        [this](VerilatedTraceBaseC* tfp, int levels, int options) { traceBaseModel(tfp, levels, options); });
}

Vcounter::Vcounter(const char* _vcname__)
    : Vcounter(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

Vcounter::~Vcounter() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void Vcounter___024root___eval_debug_assertions(Vcounter___024root* vlSelf);
#endif  // VL_DEBUG
VL_ATTR_COLD void Vcounter___024root___eval_static(Vcounter___024root* vlSelf);
VL_ATTR_COLD void Vcounter___024root___eval_initial(Vcounter___024root* vlSelf);
VL_ATTR_COLD bool Vcounter___024root___eval_stl(Vcounter___024root* vlSelf, CData/*0:0*/ firstIteration);
void Vcounter___024root___eval_sample(Vcounter___024root* vlSelf);
bool Vcounter___024root___eval_ico(Vcounter___024root* vlSelf, CData/*0:0*/ firstIteration);
bool Vcounter___024root___eval_act(Vcounter___024root* vlSelf);
bool Vcounter___024root___eval_inact(Vcounter___024root* vlSelf);
bool Vcounter___024root___eval_nba(Vcounter___024root* vlSelf);
bool Vcounter___024root___eval_obs(Vcounter___024root* vlSelf);
bool Vcounter___024root___eval_react(Vcounter___024root* vlSelf);
void Vcounter___024root___eval_postponed(Vcounter___024root* vlSelf);
VL_ATTR_COLD void Vcounter___024root___eval_final(Vcounter___024root* vlSelf);
VL_ATTR_COLD void Vcounter___024root___eval_dump_triggers__stl(Vcounter___024root* vlSelf);
VL_ATTR_COLD void Vcounter___024root___eval_dump_triggers__ico(Vcounter___024root* vlSelf);
VL_ATTR_COLD void Vcounter___024root___eval_dump_triggers__act(Vcounter___024root* vlSelf);
VL_ATTR_COLD void Vcounter___024root___eval_dump_triggers__nba(Vcounter___024root* vlSelf);
VL_ATTR_COLD void Vcounter___024root___eval_dump_triggers__obs(Vcounter___024root* vlSelf);
VL_ATTR_COLD void Vcounter___024root___eval_dump_triggers__react(Vcounter___024root* vlSelf);

void Vcounter::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vcounter::eval_step\n"); );
    m_evalLoop.eval();
}

void Vcounter::evalBegin() {
#ifdef VL_DEBUG
    // Debug assertions
    Vcounter___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_activity = true;
    vlSymsp->__Vm_deleter.deleteAll();
}

void Vcounter::evalEnd() {
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

void Vcounter::evalStatic() {
    Vcounter___024root___eval_static(&(vlSymsp->TOP));
}

void Vcounter::evalInitial() {
    Vcounter___024root___eval_initial(&(vlSymsp->TOP));
}

bool Vcounter::evalStl(bool firstIteration) {
    return Vcounter___024root___eval_stl(&(vlSymsp->TOP), firstIteration);
}

void Vcounter::evalSample() {
    Vcounter___024root___eval_sample(&(vlSymsp->TOP));
}

bool Vcounter::evalIco(bool firstIteration) {
    return Vcounter___024root___eval_ico(&(vlSymsp->TOP), firstIteration);
}

bool Vcounter::evalAct() {
    return Vcounter___024root___eval_act(&(vlSymsp->TOP));
}

bool Vcounter::evalInact() {
    return Vcounter___024root___eval_inact(&(vlSymsp->TOP));
}

bool Vcounter::evalNba() {
    return Vcounter___024root___eval_nba(&(vlSymsp->TOP));
}

bool Vcounter::evalObs() {
    return Vcounter___024root___eval_obs(&(vlSymsp->TOP));
}

bool Vcounter::evalReact() {
    return Vcounter___024root___eval_react(&(vlSymsp->TOP));
}

void Vcounter::evalPostponed() {
    Vcounter___024root___eval_postponed(&(vlSymsp->TOP));
}

void Vcounter::evalFinal() {
    Vcounter___024root___eval_final(&(vlSymsp->TOP));
}

VL_ATTR_COLD void Vcounter::dumpTriggersStl() {
    Vcounter___024root___eval_dump_triggers__stl(&(vlSymsp->TOP));
}

VL_ATTR_COLD void Vcounter::dumpTriggersIco() {
    Vcounter___024root___eval_dump_triggers__ico(&(vlSymsp->TOP));
}

VL_ATTR_COLD void Vcounter::dumpTriggersAct() {
    Vcounter___024root___eval_dump_triggers__act(&(vlSymsp->TOP));
}

VL_ATTR_COLD void Vcounter::dumpTriggersNba() {
    Vcounter___024root___eval_dump_triggers__nba(&(vlSymsp->TOP));
}

VL_ATTR_COLD void Vcounter::dumpTriggersObs() {
    Vcounter___024root___eval_dump_triggers__obs(&(vlSymsp->TOP));
}

VL_ATTR_COLD void Vcounter::dumpTriggersReact() {
    Vcounter___024root___eval_dump_triggers__react(&(vlSymsp->TOP));
}

//============================================================
// Events and timing
bool Vcounter::eventsPending() { return false; }

uint64_t Vcounter::nextTimeSlot() {
    VL_FATAL_MT(__FILE__, __LINE__, "", "No delays in the design");
    return 0;
}

//============================================================
// Utilities

const char* Vcounter::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

VL_ATTR_COLD void Vcounter::final() {
    contextp()->executingFinal(true);
    evalFinal();
    contextp()->executingFinal(false);
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* Vcounter::hierName() const { return vlSymsp->name(); }
const char* Vcounter::modelName() const { return "Vcounter"; }
unsigned Vcounter::threads() const { return 1; }
void Vcounter::prepareClone() const { contextp()->prepareClone(); }
void Vcounter::atClone() const {
    contextp()->threadPoolpOnClone();
}
std::unique_ptr<VerilatedTraceConfig> Vcounter::traceConfig() const {
    return std::unique_ptr<VerilatedTraceConfig>{new VerilatedTraceConfig{false}};
};

//============================================================
// Trace configuration

void Vcounter___024root__trace_decl_types(VerilatedVcd* tracep);

void Vcounter___024root__trace_init_top(Vcounter___024root* vlSelf, VerilatedVcd* tracep);

VL_ATTR_COLD static void trace_init(void* voidSelf, VerilatedVcd* tracep, uint32_t code) {
    // Callback from tracep->open()
    Vcounter___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vcounter___024root*>(voidSelf);
    Vcounter__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (!vlSymsp->_vm_contextp__->calcUnusedSigs()) {
        VL_FATAL_MT(__FILE__, __LINE__, __FILE__,
            "Turning on wave traces requires Verilated::traceEverOn(true) call before time 0.");
    }
    vlSymsp->__Vm_baseCode = code;
    tracep->pushPrefix(vlSymsp->name(), VerilatedTracePrefixType::SCOPE_MODULE);
    Vcounter___024root__trace_decl_types(tracep);
    Vcounter___024root__trace_init_top(vlSelf, tracep);
    tracep->popPrefix();
}

VL_ATTR_COLD void Vcounter___024root__trace_register(Vcounter___024root* vlSelf, VerilatedVcd* tracep);

VL_ATTR_COLD void Vcounter::traceBaseModel(VerilatedTraceBaseC* tfp, int levels, int options) {
    (void)levels; (void)options;
    VerilatedVcdC* const stfp = dynamic_cast<VerilatedVcdC*>(tfp);
    if (VL_UNLIKELY(!stfp)) {
        vl_fatal(__FILE__, __LINE__, __FILE__,"'Vcounter::trace()' called on non-VerilatedVcdC object;"
            " use --trace-fst with VerilatedFst object, and --trace-vcd with VerilatedVcd object");
    }
    stfp->spTrace()->addModel(this);
    stfp->spTrace()->addInitCb(&trace_init, &(vlSymsp->TOP), name(), false, 5);
    Vcounter___024root__trace_register(&(vlSymsp->TOP), stfp->spTrace());
}
