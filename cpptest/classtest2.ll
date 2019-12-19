; ModuleID = 'classtest2.cpp'
source_filename = "classtest2.cpp"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%class.A = type { i32 (...)** }
%class.B = type { %class.A }

$_ZN1AC2Ev = comdat any

$_ZN1BC2Ev = comdat any

$_ZN1A2m1Ev = comdat any

$_ZN1A2m2Ev = comdat any

$_ZN1B2m2Ev = comdat any

$_ZTV1A = comdat any

$_ZTS1A = comdat any

$_ZTI1A = comdat any

$_ZTV1B = comdat any

$_ZTS1B = comdat any

$_ZTI1B = comdat any

@_ZTV1A = linkonce_odr dso_local unnamed_addr constant { [4 x i8*] } { [4 x i8*] [i8* null, i8* bitcast ({ i8*, i8* }* @_ZTI1A to i8*), i8* bitcast (i32 (%class.A*)* @_ZN1A2m1Ev to i8*), i8* bitcast (i32 (%class.A*)* @_ZN1A2m2Ev to i8*)] }, comdat, align 8
@_ZTVN10__cxxabiv117__class_type_infoE = external dso_local global i8*
@_ZTS1A = linkonce_odr dso_local constant [3 x i8] c"1A\00", comdat, align 1
@_ZTI1A = linkonce_odr dso_local constant { i8*, i8* } { i8* bitcast (i8** getelementptr inbounds (i8*, i8** @_ZTVN10__cxxabiv117__class_type_infoE, i64 2) to i8*), i8* getelementptr inbounds ([3 x i8], [3 x i8]* @_ZTS1A, i32 0, i32 0) }, comdat, align 8
@_ZTV1B = linkonce_odr dso_local unnamed_addr constant { [4 x i8*] } { [4 x i8*] [i8* null, i8* bitcast ({ i8*, i8*, i8* }* @_ZTI1B to i8*), i8* bitcast (i32 (%class.A*)* @_ZN1A2m1Ev to i8*), i8* bitcast (i32 (%class.B*)* @_ZN1B2m2Ev to i8*)] }, comdat, align 8
@_ZTVN10__cxxabiv120__si_class_type_infoE = external dso_local global i8*
@_ZTS1B = linkonce_odr dso_local constant [3 x i8] c"1B\00", comdat, align 1
@_ZTI1B = linkonce_odr dso_local constant { i8*, i8*, i8* } { i8* bitcast (i8** getelementptr inbounds (i8*, i8** @_ZTVN10__cxxabiv120__si_class_type_infoE, i64 2) to i8*), i8* getelementptr inbounds ([3 x i8], [3 x i8]* @_ZTS1B, i32 0, i32 0), i8* bitcast ({ i8*, i8* }* @_ZTI1A to i8*) }, comdat, align 8

; Function Attrs: noinline norecurse optnone uwtable
define dso_local i32 @main() #0 {
entry:
  %retval = alloca i32, align 4
  %testA = alloca %class.A*, align 8
  %testB = alloca %class.B*, align 8
  store i32 0, i32* %retval, align 4
  %call = call i8* @_Znwm(i64 8) #4
  %0 = bitcast i8* %call to %class.A*
  %1 = bitcast %class.A* %0 to i8*
  call void @llvm.memset.p0i8.i64(i8* align 8 %1, i8 0, i64 8, i1 false)
  call void @_ZN1AC2Ev(%class.A* %0) #5
  store %class.A* %0, %class.A** %testA, align 8
  %call1 = call i8* @_Znwm(i64 8) #4
  %2 = bitcast i8* %call1 to %class.B*
  %3 = bitcast %class.B* %2 to i8*
  call void @llvm.memset.p0i8.i64(i8* align 8 %3, i8 0, i64 8, i1 false)
  call void @_ZN1BC2Ev(%class.B* %2) #5
  store %class.B* %2, %class.B** %testB, align 8
  %4 = load %class.A*, %class.A** %testA, align 8
  %5 = bitcast %class.A* %4 to i32 (%class.A*)***
  %vtable = load i32 (%class.A*)**, i32 (%class.A*)*** %5, align 8
  %vfn = getelementptr inbounds i32 (%class.A*)*, i32 (%class.A*)** %vtable, i64 0
  %6 = load i32 (%class.A*)*, i32 (%class.A*)** %vfn, align 8
  %call2 = call i32 %6(%class.A* %4)
  %call3 = call i8* @_Znwm(i64 8) #4
  %7 = bitcast i8* %call3 to %class.B*
  %8 = bitcast %class.B* %7 to i8*
  call void @llvm.memset.p0i8.i64(i8* align 8 %8, i8 0, i64 8, i1 false)
  call void @_ZN1BC2Ev(%class.B* %7) #5
  %9 = bitcast %class.B* %7 to %class.A*
  store %class.A* %9, %class.A** %testA, align 8
  %10 = load %class.A*, %class.A** %testA, align 8
  %11 = bitcast %class.A* %10 to i32 (%class.A*)***
  %vtable4 = load i32 (%class.A*)**, i32 (%class.A*)*** %11, align 8
  %vfn5 = getelementptr inbounds i32 (%class.A*)*, i32 (%class.A*)** %vtable4, i64 0
  %12 = load i32 (%class.A*)*, i32 (%class.A*)** %vfn5, align 8
  %call6 = call i32 %12(%class.A* %10)
  %13 = load %class.B*, %class.B** %testB, align 8
  %14 = bitcast %class.B* %13 to %class.A*
  %15 = bitcast %class.A* %14 to i32 (%class.A*)***
  %vtable7 = load i32 (%class.A*)**, i32 (%class.A*)*** %15, align 8
  %vfn8 = getelementptr inbounds i32 (%class.A*)*, i32 (%class.A*)** %vtable7, i64 0
  %16 = load i32 (%class.A*)*, i32 (%class.A*)** %vfn8, align 8
  %call9 = call i32 %16(%class.A* %14)
  %17 = load %class.A*, %class.A** %testA, align 8
  %18 = bitcast %class.A* %17 to i32 (%class.A*)***
  %vtable10 = load i32 (%class.A*)**, i32 (%class.A*)*** %18, align 8
  %vfn11 = getelementptr inbounds i32 (%class.A*)*, i32 (%class.A*)** %vtable10, i64 1
  %19 = load i32 (%class.A*)*, i32 (%class.A*)** %vfn11, align 8
  %call12 = call i32 %19(%class.A* %17)
  %20 = load %class.B*, %class.B** %testB, align 8
  %21 = bitcast %class.B* %20 to i32 (%class.B*)***
  %vtable13 = load i32 (%class.B*)**, i32 (%class.B*)*** %21, align 8
  %vfn14 = getelementptr inbounds i32 (%class.B*)*, i32 (%class.B*)** %vtable13, i64 1
  %22 = load i32 (%class.B*)*, i32 (%class.B*)** %vfn14, align 8
  %call15 = call i32 %22(%class.B* %20)
  ret i32 0
}

; Function Attrs: nobuiltin
declare dso_local noalias i8* @_Znwm(i64) #1

; Function Attrs: argmemonly nounwind
declare void @llvm.memset.p0i8.i64(i8* nocapture writeonly, i8, i64, i1 immarg) #2

; Function Attrs: noinline nounwind optnone uwtable
define linkonce_odr dso_local void @_ZN1AC2Ev(%class.A* %this) unnamed_addr #3 comdat align 2 {
entry:
  %this.addr = alloca %class.A*, align 8
  store %class.A* %this, %class.A** %this.addr, align 8
  %this1 = load %class.A*, %class.A** %this.addr, align 8
  %0 = bitcast %class.A* %this1 to i32 (...)***
  store i32 (...)** bitcast (i8** getelementptr inbounds ({ [4 x i8*] }, { [4 x i8*] }* @_ZTV1A, i32 0, inrange i32 0, i32 2) to i32 (...)**), i32 (...)*** %0, align 8
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define linkonce_odr dso_local void @_ZN1BC2Ev(%class.B* %this) unnamed_addr #3 comdat align 2 {
entry:
  %this.addr = alloca %class.B*, align 8
  store %class.B* %this, %class.B** %this.addr, align 8
  %this1 = load %class.B*, %class.B** %this.addr, align 8
  %0 = bitcast %class.B* %this1 to %class.A*
  call void @_ZN1AC2Ev(%class.A* %0) #5
  %1 = bitcast %class.B* %this1 to i32 (...)***
  store i32 (...)** bitcast (i8** getelementptr inbounds ({ [4 x i8*] }, { [4 x i8*] }* @_ZTV1B, i32 0, inrange i32 0, i32 2) to i32 (...)**), i32 (...)*** %1, align 8
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define linkonce_odr dso_local i32 @_ZN1A2m1Ev(%class.A* %this) unnamed_addr #3 comdat align 2 {
entry:
  %this.addr = alloca %class.A*, align 8
  store %class.A* %this, %class.A** %this.addr, align 8
  %this1 = load %class.A*, %class.A** %this.addr, align 8
  ret i32 0
}

; Function Attrs: noinline nounwind optnone uwtable
define linkonce_odr dso_local i32 @_ZN1A2m2Ev(%class.A* %this) unnamed_addr #3 comdat align 2 {
entry:
  %this.addr = alloca %class.A*, align 8
  store %class.A* %this, %class.A** %this.addr, align 8
  %this1 = load %class.A*, %class.A** %this.addr, align 8
  ret i32 1
}

; Function Attrs: noinline nounwind optnone uwtable
define linkonce_odr dso_local i32 @_ZN1B2m2Ev(%class.B* %this) unnamed_addr #3 comdat align 2 {
entry:
  %this.addr = alloca %class.B*, align 8
  store %class.B* %this, %class.B** %this.addr, align 8
  %this1 = load %class.B*, %class.B** %this.addr, align 8
  ret i32 2
}

attributes #0 = { noinline norecurse optnone uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nobuiltin "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #2 = { argmemonly nounwind }
attributes #3 = { noinline nounwind optnone uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { builtin }
attributes #5 = { nounwind }

!llvm.module.flags = !{!0}
!llvm.ident = !{!1}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{!"clang version 9.0.0 (/home/guest/llvm-project/clang dbc681189a0397608ca75e8f7d5a57e0cf01a040)"}
