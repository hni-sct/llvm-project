//===-- RISCV.h - Top-level interface for RISCV -----------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file contains the entry points for global functions defined in the LLVM
// RISC-V back-end.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_RISCV_RISCV_H
#define LLVM_LIB_TARGET_RISCV_RISCV_H

#include "MCTargetDesc/RISCVBaseInfo.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/Support/CommandLine.h"

namespace llvm::cl {
inline opt<bool> enable_cfcss{"CFCSS", desc("CFCSS pass for CFP"),
                              value_desc("pass")};
inline opt<bool> enable_rasm{"RASM", desc("RASM pass for CFP"),
                             value_desc("pass")};
inline opt<bool> enable_nzdc{"NZDC", desc("NZDC pass for DFP"),
                             value_desc("pass")};
inline opt<bool> enable_fgs{"FGS", desc("fine grain schedule for instr. DMR"),
                            value_desc("pass")};
inline opt<bool> reserve_rf{"RRF", desc("reserve half of RegFiles"),
                            value_desc("pass")};
inline opt<bool> enable_repair{"REPAIR", desc("REPAIR pass on top of DMR"),
                               value_desc("pass")};
}  // namespace llvm::cl

namespace llvm {
class RISCVRegisterBankInfo;
class RISCVSubtarget;
class RISCVTargetMachine;
class AsmPrinter;
class FunctionPass;
class InstructionSelector;
class MCInst;
class MCOperand;
class MachineInstr;
class MachineOperand;
class PassRegistry;

void LowerRISCVMachineInstrToMCInst(const MachineInstr *MI, MCInst &OutMI,
                                    const AsmPrinter &AP);
bool LowerRISCVMachineOperandToMCOperand(const MachineOperand &MO,
                                         MCOperand &MCOp, const AsmPrinter &AP);

FunctionPass *createRISCVISelDag(RISCVTargetMachine &TM);

FunctionPass *createRISCVMergeBaseOffsetOptPass();
void initializeRISCVMergeBaseOffsetOptPass(PassRegistry &);

FunctionPass *createRISCVExpandPseudoPass();
void initializeRISCVExpandPseudoPass(PassRegistry &);

FunctionPass *createRISCVExpandAtomicPseudoPass();
void initializeRISCVExpandAtomicPseudoPass(PassRegistry &);

FunctionPass *createRISCVCleanupVSETVLIPass();
void initializeRISCVCleanupVSETVLIPass(PassRegistry &);

FunctionPass *createRISCVCfcss();
FunctionPass *createRISCVRasm();
FunctionPass *createRISCVDmr();

InstructionSelector *createRISCVInstructionSelector(const RISCVTargetMachine &,
                                                    RISCVSubtarget &,
                                                    RISCVRegisterBankInfo &);
}

#endif
