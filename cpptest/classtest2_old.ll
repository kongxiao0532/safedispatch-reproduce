; ModuleID = 'classtest2.cpp'
source_filename = "classtest2.cpp"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%class.A = type { i8 }
%class.B = type { i8 }

$_ZN1A2m1Ev = comdat any

@.str = private unnamed_addr constant [8 x i8] c"m1 in A\00", align 1
; Function Attrs: noinline norecurse optnone uwtable
define dso_local i32 @main() #0 {
entry:
  %retval = alloca i32, align 4
  %testA = alloca %class.A*, align 8
  store i32 0, i32* %retval, align 4
  %call = call i8* @_Znwm(i64 1) #4
  %0 = bitcast i8* %call to %class.A*
  store %class.A* %0, %class.A** %testA, align 8
  %1 = load %class.A*, %class.A** %testA, align 8
  call void @_ZN1A2m1Ev(%class.A* %1)
  %call1 = call i8* @_Znwm(i64 1) #4
  %2 = bitcast i8* %call1 to %class.B*
  %3 = bitcast %class.B* %2 to %class.A*
  store %class.A* %3, %class.A** %testA, align 8
  %4 = load %class.A*, %class.A** %testA, align 8
  call void @_ZN1A2m1Ev(%class.A* %4)
  ret i32 0
}
; Function Attrs: nobuiltin
declare dso_local noalias i8* @_Znwm(i64) #1
; Function Attrs: noinline optnone uwtable
define linkonce_odr dso_local void @_ZN1A2m1Ev(%class.A* %this) #2 comdat align 2 {
entry:
  %this.addr = alloca %class.A*, align 8
  store %class.A* %this, %class.A** %this.addr, align 8
  %this1 = load %class.A*, %class.A** %this.addr, align 8
  %call = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str, i64 0, i64 0))
  ret void
}
declare dso_local i32 @printf(i8*, ...) #3

attributes #0 = { noinline norecurse optnone uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nobuiltin "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #2 = { noinline optnone uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { builtin }

!llvm.module.flags = !{!0}
!llvm.ident = !{!1}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{!"clang version 10.0.0 (https://github.com/llvm/llvm-project.git 902dc6c69ce7985427efa103a7c4099c372da6fa)"}
