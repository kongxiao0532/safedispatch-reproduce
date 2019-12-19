; ModuleID = 'classtest.cpp'
source_filename = "classtest.cpp"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%class.A = type { i32 (...)** }
%class.B = type { %class.A }
%class.C = type { %class.A }
%class.D = type { %class.C }
%class.E = type { %class.C }

$_ZN1AC2Ev = comdat any

$_ZN1CC2Ev = comdat any

$_ZN1EC2Ev = comdat any

$_ZN1BC2Ev = comdat any

$_ZN1DC2Ev = comdat any

$_ZN1A2m1Ev = comdat any

$_ZN1A2m2Ev = comdat any

$_ZN1A2m3Ev = comdat any

$_ZN1B2m1Ev = comdat any

$_ZN1C2m1Ev = comdat any

$_ZN1D2m2Ev = comdat any

$_ZN1E2m3Ev = comdat any

$_ZN1A2m1Ei = comdat any

$_ZN1A3fooEv = comdat any

$_ZN1B2m1Ei = comdat any

$_ZN1B3fooEv = comdat any

$_ZTV1A = comdat any

$_ZTS1A = comdat any

$_ZTI1A = comdat any

$_ZTV1C = comdat any

$_ZTS1C = comdat any

$_ZTI1C = comdat any

$_ZTV1E = comdat any

$_ZTS1E = comdat any

$_ZTI1E = comdat any

$_ZTV1B = comdat any

$_ZTS1B = comdat any

$_ZTI1B = comdat any

$_ZTV1D = comdat any

$_ZTS1D = comdat any

$_ZTI1D = comdat any

@_ZTV1A = linkonce_odr dso_local unnamed_addr constant { [7 x i8*] } { [7 x i8*] [i8* null, i8* bitcast ({ i8*, i8* }* @_ZTI1A to i8*), i8* bitcast (void (%class.A*)* @_ZN1A2m1Ev to i8*), i8* bitcast (void (%class.A*, i32)* @_ZN1A2m1Ei to i8*), i8* bitcast (void (%class.A*)* @_ZN1A2m2Ev to i8*), i8* bitcast (void (%class.A*)* @_ZN1A2m3Ev to i8*), i8* bitcast (void (%class.A*)* @_ZN1A3fooEv to i8*)] }, comdat, align 8
@_ZTVN10__cxxabiv117__class_type_infoE = external dso_local global i8*
@_ZTS1A = linkonce_odr dso_local constant [3 x i8] c"1A\00", comdat, align 1
@_ZTI1A = linkonce_odr dso_local constant { i8*, i8* } { i8* bitcast (i8** getelementptr inbounds (i8*, i8** @_ZTVN10__cxxabiv117__class_type_infoE, i64 2) to i8*), i8* getelementptr inbounds ([3 x i8], [3 x i8]* @_ZTS1A, i32 0, i32 0) }, comdat, align 8
@_ZTV1C = linkonce_odr dso_local unnamed_addr constant { [7 x i8*] } { [7 x i8*] [i8* null, i8* bitcast ({ i8*, i8*, i8* }* @_ZTI1C to i8*), i8* bitcast (void (%class.C*)* @_ZN1C2m1Ev to i8*), i8* bitcast (void (%class.A*, i32)* @_ZN1A2m1Ei to i8*), i8* bitcast (void (%class.A*)* @_ZN1A2m2Ev to i8*), i8* bitcast (void (%class.A*)* @_ZN1A2m3Ev to i8*), i8* bitcast (void (%class.A*)* @_ZN1A3fooEv to i8*)] }, comdat, align 8
@_ZTVN10__cxxabiv120__si_class_type_infoE = external dso_local global i8*
@_ZTS1C = linkonce_odr dso_local constant [3 x i8] c"1C\00", comdat, align 1
@_ZTI1C = linkonce_odr dso_local constant { i8*, i8*, i8* } { i8* bitcast (i8** getelementptr inbounds (i8*, i8** @_ZTVN10__cxxabiv120__si_class_type_infoE, i64 2) to i8*), i8* getelementptr inbounds ([3 x i8], [3 x i8]* @_ZTS1C, i32 0, i32 0), i8* bitcast ({ i8*, i8* }* @_ZTI1A to i8*) }, comdat, align 8
@_ZTV1E = linkonce_odr dso_local unnamed_addr constant { [7 x i8*] } { [7 x i8*] [i8* null, i8* bitcast ({ i8*, i8*, i8* }* @_ZTI1E to i8*), i8* bitcast (void (%class.C*)* @_ZN1C2m1Ev to i8*), i8* bitcast (void (%class.A*, i32)* @_ZN1A2m1Ei to i8*), i8* bitcast (void (%class.A*)* @_ZN1A2m2Ev to i8*), i8* bitcast (void (%class.E*)* @_ZN1E2m3Ev to i8*), i8* bitcast (void (%class.A*)* @_ZN1A3fooEv to i8*)] }, comdat, align 8
@_ZTS1E = linkonce_odr dso_local constant [3 x i8] c"1E\00", comdat, align 1
@_ZTI1E = linkonce_odr dso_local constant { i8*, i8*, i8* } { i8* bitcast (i8** getelementptr inbounds (i8*, i8** @_ZTVN10__cxxabiv120__si_class_type_infoE, i64 2) to i8*), i8* getelementptr inbounds ([3 x i8], [3 x i8]* @_ZTS1E, i32 0, i32 0), i8* bitcast ({ i8*, i8*, i8* }* @_ZTI1C to i8*) }, comdat, align 8
@_ZTV1B = linkonce_odr dso_local unnamed_addr constant { [7 x i8*] } { [7 x i8*] [i8* null, i8* bitcast ({ i8*, i8*, i8* }* @_ZTI1B to i8*), i8* bitcast (void (%class.B*)* @_ZN1B2m1Ev to i8*), i8* bitcast (void (%class.B*, i32)* @_ZN1B2m1Ei to i8*), i8* bitcast (void (%class.A*)* @_ZN1A2m2Ev to i8*), i8* bitcast (void (%class.A*)* @_ZN1A2m3Ev to i8*), i8* bitcast (void (%class.B*)* @_ZN1B3fooEv to i8*)] }, comdat, align 8
@_ZTS1B = linkonce_odr dso_local constant [3 x i8] c"1B\00", comdat, align 1
@_ZTI1B = linkonce_odr dso_local constant { i8*, i8*, i8* } { i8* bitcast (i8** getelementptr inbounds (i8*, i8** @_ZTVN10__cxxabiv120__si_class_type_infoE, i64 2) to i8*), i8* getelementptr inbounds ([3 x i8], [3 x i8]* @_ZTS1B, i32 0, i32 0), i8* bitcast ({ i8*, i8* }* @_ZTI1A to i8*) }, comdat, align 8
@_ZTV1D = linkonce_odr dso_local unnamed_addr constant { [7 x i8*] } { [7 x i8*] [i8* null, i8* bitcast ({ i8*, i8*, i8* }* @_ZTI1D to i8*), i8* bitcast (void (%class.C*)* @_ZN1C2m1Ev to i8*), i8* bitcast (void (%class.A*, i32)* @_ZN1A2m1Ei to i8*), i8* bitcast (void (%class.D*)* @_ZN1D2m2Ev to i8*), i8* bitcast (void (%class.A*)* @_ZN1A2m3Ev to i8*), i8* bitcast (void (%class.A*)* @_ZN1A3fooEv to i8*)] }, comdat, align 8
@_ZTS1D = linkonce_odr dso_local constant [3 x i8] c"1D\00", comdat, align 1
@_ZTI1D = linkonce_odr dso_local constant { i8*, i8*, i8* } { i8* bitcast (i8** getelementptr inbounds (i8*, i8** @_ZTVN10__cxxabiv120__si_class_type_infoE, i64 2) to i8*), i8* getelementptr inbounds ([3 x i8], [3 x i8]* @_ZTS1D, i32 0, i32 0), i8* bitcast ({ i8*, i8*, i8* }* @_ZTI1C to i8*) }, comdat, align 8

; Function Attrs: noinline norecurse optnone uwtable
define dso_local i32 @main() #0 {
entry:
  %retval = alloca i32, align 4
  %testA = alloca %class.A*, align 8
  %f = alloca { i64, i64 }, align 8
  %a = alloca %class.A, align 8
  %b = alloca %class.B, align 8
  %c = alloca %class.C, align 8
  %d = alloca %class.D, align 8
  %e = alloca %class.E, align 8
  store i32 0, i32* %retval, align 4
  %call = call i8* @_Znwm(i64 8) #4
  %0 = bitcast i8* %call to %class.A*
  %1 = bitcast %class.A* %0 to i8*
  call void @llvm.memset.p0i8.i64(i8* align 8 %1, i8 0, i64 8, i1 false)
  call void @_ZN1AC2Ev(%class.A* %0) #5
  store %class.A* %0, %class.A** %testA, align 8
  %2 = load %class.A*, %class.A** %testA, align 8
  %3 = bitcast %class.A* %2 to void (%class.A*)***
  %vtable = load void (%class.A*)**, void (%class.A*)*** %3, align 8
  %vfn = getelementptr inbounds void (%class.A*)*, void (%class.A*)** %vtable, i64 3
  %4 = load void (%class.A*)*, void (%class.A*)** %vfn, align 8
  call void %4(%class.A* %2)
  %call1 = call i8* @_Znwm(i64 8) #4
  %5 = bitcast i8* %call1 to %class.C*
  %6 = bitcast %class.C* %5 to i8*
  call void @llvm.memset.p0i8.i64(i8* align 8 %6, i8 0, i64 8, i1 false)
  call void @_ZN1CC2Ev(%class.C* %5) #5
  %7 = bitcast %class.C* %5 to %class.A*
  store %class.A* %7, %class.A** %testA, align 8
  %8 = load %class.A*, %class.A** %testA, align 8
  %9 = bitcast %class.A* %8 to void (%class.A*)***
  %vtable2 = load void (%class.A*)**, void (%class.A*)*** %9, align 8
  %vfn3 = getelementptr inbounds void (%class.A*)*, void (%class.A*)** %vtable2, i64 3
  %10 = load void (%class.A*)*, void (%class.A*)** %vfn3, align 8
  call void %10(%class.A* %8)
  %call4 = call i8* @_Znwm(i64 8) #4
  %11 = bitcast i8* %call4 to %class.E*
  %12 = bitcast %class.E* %11 to i8*
  call void @llvm.memset.p0i8.i64(i8* align 8 %12, i8 0, i64 8, i1 false)
  call void @_ZN1EC2Ev(%class.E* %11) #5
  %13 = bitcast %class.E* %11 to %class.A*
  store %class.A* %13, %class.A** %testA, align 8
  %14 = load %class.A*, %class.A** %testA, align 8
  %15 = bitcast %class.A* %14 to void (%class.A*)***
  %vtable5 = load void (%class.A*)**, void (%class.A*)*** %15, align 8
  %vfn6 = getelementptr inbounds void (%class.A*)*, void (%class.A*)** %vtable5, i64 3
  %16 = load void (%class.A*)*, void (%class.A*)** %vfn6, align 8
  call void %16(%class.A* %14)
  store { i64, i64 } { i64 33, i64 0 }, { i64, i64 }* %f, align 8
  %call7 = call i8* @_Znwm(i64 8) #4
  %17 = bitcast i8* %call7 to %class.A*
  %18 = bitcast %class.A* %17 to i8*
  call void @llvm.memset.p0i8.i64(i8* align 8 %18, i8 0, i64 8, i1 false)
  call void @_ZN1AC2Ev(%class.A* %17) #5
  store %class.A* %17, %class.A** %testA, align 8
  %19 = load %class.A*, %class.A** %testA, align 8
  %20 = load { i64, i64 }, { i64, i64 }* %f, align 8
  %memptr.adj = extractvalue { i64, i64 } %20, 1
  %21 = bitcast %class.A* %19 to i8*
  %22 = getelementptr inbounds i8, i8* %21, i64 %memptr.adj
  %this.adjusted = bitcast i8* %22 to %class.A*
  %memptr.ptr = extractvalue { i64, i64 } %20, 0
  %23 = and i64 %memptr.ptr, 1
  %memptr.isvirtual = icmp ne i64 %23, 0
  br i1 %memptr.isvirtual, label %memptr.virtual, label %memptr.nonvirtual

memptr.virtual:                                   ; preds = %entry
  %24 = bitcast %class.A* %this.adjusted to i8**
  %vtable8 = load i8*, i8** %24, align 8
  %25 = sub i64 %memptr.ptr, 1
  %26 = getelementptr i8, i8* %vtable8, i64 %25
  %27 = bitcast i8* %26 to void (%class.A*)**
  %memptr.virtualfn = load void (%class.A*)*, void (%class.A*)** %27, align 8
  br label %memptr.end

memptr.nonvirtual:                                ; preds = %entry
  %memptr.nonvirtualfn = inttoptr i64 %memptr.ptr to void (%class.A*)*
  br label %memptr.end

memptr.end:                                       ; preds = %memptr.nonvirtual, %memptr.virtual
  %28 = phi void (%class.A*)* [ %memptr.virtualfn, %memptr.virtual ], [ %memptr.nonvirtualfn, %memptr.nonvirtual ]
  call void %28(%class.A* %this.adjusted)
  %call9 = call i8* @_Znwm(i64 8) #4
  %29 = bitcast i8* %call9 to %class.B*
  %30 = bitcast %class.B* %29 to i8*
  call void @llvm.memset.p0i8.i64(i8* align 8 %30, i8 0, i64 8, i1 false)
  call void @_ZN1BC2Ev(%class.B* %29) #5
  %31 = bitcast %class.B* %29 to %class.A*
  store %class.A* %31, %class.A** %testA, align 8
  %32 = load %class.A*, %class.A** %testA, align 8
  %33 = load { i64, i64 }, { i64, i64 }* %f, align 8
  %memptr.adj10 = extractvalue { i64, i64 } %33, 1
  %34 = bitcast %class.A* %32 to i8*
  %35 = getelementptr inbounds i8, i8* %34, i64 %memptr.adj10
  %this.adjusted11 = bitcast i8* %35 to %class.A*
  %memptr.ptr12 = extractvalue { i64, i64 } %33, 0
  %36 = and i64 %memptr.ptr12, 1
  %memptr.isvirtual13 = icmp ne i64 %36, 0
  br i1 %memptr.isvirtual13, label %memptr.virtual14, label %memptr.nonvirtual17

memptr.virtual14:                                 ; preds = %memptr.end
  %37 = bitcast %class.A* %this.adjusted11 to i8**
  %vtable15 = load i8*, i8** %37, align 8
  %38 = sub i64 %memptr.ptr12, 1
  %39 = getelementptr i8, i8* %vtable15, i64 %38
  %40 = bitcast i8* %39 to void (%class.A*)**
  %memptr.virtualfn16 = load void (%class.A*)*, void (%class.A*)** %40, align 8
  br label %memptr.end19

memptr.nonvirtual17:                              ; preds = %memptr.end
  %memptr.nonvirtualfn18 = inttoptr i64 %memptr.ptr12 to void (%class.A*)*
  br label %memptr.end19

memptr.end19:                                     ; preds = %memptr.nonvirtual17, %memptr.virtual14
  %41 = phi void (%class.A*)* [ %memptr.virtualfn16, %memptr.virtual14 ], [ %memptr.nonvirtualfn18, %memptr.nonvirtual17 ]
  call void %41(%class.A* %this.adjusted11)
  call void @_ZN1AC2Ev(%class.A* %a) #5
  call void @_ZN1BC2Ev(%class.B* %b) #5
  call void @_ZN1CC2Ev(%class.C* %c) #5
  call void @_ZN1DC2Ev(%class.D* %d) #5
  call void @_ZN1EC2Ev(%class.E* %e) #5
  call void @_ZN1A2m1Ev(%class.A* %a)
  call void @_ZN1A2m2Ev(%class.A* %a)
  call void @_ZN1A2m3Ev(%class.A* %a)
  call void @_ZN1B2m1Ev(%class.B* %b)
  %42 = bitcast %class.B* %b to %class.A*
  call void @_ZN1A2m2Ev(%class.A* %42)
  %43 = bitcast %class.B* %b to %class.A*
  call void @_ZN1A2m3Ev(%class.A* %43)
  call void @_ZN1C2m1Ev(%class.C* %c)
  %44 = bitcast %class.C* %c to %class.A*
  call void @_ZN1A2m2Ev(%class.A* %44)
  %45 = bitcast %class.C* %c to %class.A*
  call void @_ZN1A2m3Ev(%class.A* %45)
  %46 = bitcast %class.D* %d to %class.C*
  call void @_ZN1C2m1Ev(%class.C* %46)
  call void @_ZN1D2m2Ev(%class.D* %d)
  %47 = bitcast %class.D* %d to %class.A*
  call void @_ZN1A2m3Ev(%class.A* %47)
  %48 = bitcast %class.E* %e to %class.C*
  call void @_ZN1C2m1Ev(%class.C* %48)
  %49 = bitcast %class.E* %e to %class.A*
  call void @_ZN1A2m2Ev(%class.A* %49)
  call void @_ZN1E2m3Ev(%class.E* %e)
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
  store i32 (...)** bitcast (i8** getelementptr inbounds ({ [7 x i8*] }, { [7 x i8*] }* @_ZTV1A, i32 0, inrange i32 0, i32 2) to i32 (...)**), i32 (...)*** %0, align 8
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define linkonce_odr dso_local void @_ZN1CC2Ev(%class.C* %this) unnamed_addr #3 comdat align 2 {
entry:
  %this.addr = alloca %class.C*, align 8
  store %class.C* %this, %class.C** %this.addr, align 8
  %this1 = load %class.C*, %class.C** %this.addr, align 8
  %0 = bitcast %class.C* %this1 to %class.A*
  call void @_ZN1AC2Ev(%class.A* %0) #5
  %1 = bitcast %class.C* %this1 to i32 (...)***
  store i32 (...)** bitcast (i8** getelementptr inbounds ({ [7 x i8*] }, { [7 x i8*] }* @_ZTV1C, i32 0, inrange i32 0, i32 2) to i32 (...)**), i32 (...)*** %1, align 8
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define linkonce_odr dso_local void @_ZN1EC2Ev(%class.E* %this) unnamed_addr #3 comdat align 2 {
entry:
  %this.addr = alloca %class.E*, align 8
  store %class.E* %this, %class.E** %this.addr, align 8
  %this1 = load %class.E*, %class.E** %this.addr, align 8
  %0 = bitcast %class.E* %this1 to %class.C*
  call void @_ZN1CC2Ev(%class.C* %0) #5
  %1 = bitcast %class.E* %this1 to i32 (...)***
  store i32 (...)** bitcast (i8** getelementptr inbounds ({ [7 x i8*] }, { [7 x i8*] }* @_ZTV1E, i32 0, inrange i32 0, i32 2) to i32 (...)**), i32 (...)*** %1, align 8
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
  store i32 (...)** bitcast (i8** getelementptr inbounds ({ [7 x i8*] }, { [7 x i8*] }* @_ZTV1B, i32 0, inrange i32 0, i32 2) to i32 (...)**), i32 (...)*** %1, align 8
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define linkonce_odr dso_local void @_ZN1DC2Ev(%class.D* %this) unnamed_addr #3 comdat align 2 {
entry:
  %this.addr = alloca %class.D*, align 8
  store %class.D* %this, %class.D** %this.addr, align 8
  %this1 = load %class.D*, %class.D** %this.addr, align 8
  %0 = bitcast %class.D* %this1 to %class.C*
  call void @_ZN1CC2Ev(%class.C* %0) #5
  %1 = bitcast %class.D* %this1 to i32 (...)***
  store i32 (...)** bitcast (i8** getelementptr inbounds ({ [7 x i8*] }, { [7 x i8*] }* @_ZTV1D, i32 0, inrange i32 0, i32 2) to i32 (...)**), i32 (...)*** %1, align 8
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define linkonce_odr dso_local void @_ZN1A2m1Ev(%class.A* %this) unnamed_addr #3 comdat align 2 {
entry:
  %this.addr = alloca %class.A*, align 8
  store %class.A* %this, %class.A** %this.addr, align 8
  %this1 = load %class.A*, %class.A** %this.addr, align 8
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define linkonce_odr dso_local void @_ZN1A2m2Ev(%class.A* %this) unnamed_addr #3 comdat align 2 {
entry:
  %this.addr = alloca %class.A*, align 8
  store %class.A* %this, %class.A** %this.addr, align 8
  %this1 = load %class.A*, %class.A** %this.addr, align 8
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define linkonce_odr dso_local void @_ZN1A2m3Ev(%class.A* %this) unnamed_addr #3 comdat align 2 {
entry:
  %this.addr = alloca %class.A*, align 8
  store %class.A* %this, %class.A** %this.addr, align 8
  %this1 = load %class.A*, %class.A** %this.addr, align 8
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define linkonce_odr dso_local void @_ZN1B2m1Ev(%class.B* %this) unnamed_addr #3 comdat align 2 {
entry:
  %this.addr = alloca %class.B*, align 8
  store %class.B* %this, %class.B** %this.addr, align 8
  %this1 = load %class.B*, %class.B** %this.addr, align 8
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define linkonce_odr dso_local void @_ZN1C2m1Ev(%class.C* %this) unnamed_addr #3 comdat align 2 {
entry:
  %this.addr = alloca %class.C*, align 8
  store %class.C* %this, %class.C** %this.addr, align 8
  %this1 = load %class.C*, %class.C** %this.addr, align 8
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define linkonce_odr dso_local void @_ZN1D2m2Ev(%class.D* %this) unnamed_addr #3 comdat align 2 {
entry:
  %this.addr = alloca %class.D*, align 8
  store %class.D* %this, %class.D** %this.addr, align 8
  %this1 = load %class.D*, %class.D** %this.addr, align 8
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define linkonce_odr dso_local void @_ZN1E2m3Ev(%class.E* %this) unnamed_addr #3 comdat align 2 {
entry:
  %this.addr = alloca %class.E*, align 8
  store %class.E* %this, %class.E** %this.addr, align 8
  %this1 = load %class.E*, %class.E** %this.addr, align 8
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define linkonce_odr dso_local void @_ZN1A2m1Ei(%class.A* %this, i32 %a) unnamed_addr #3 comdat align 2 {
entry:
  %this.addr = alloca %class.A*, align 8
  %a.addr = alloca i32, align 4
  store %class.A* %this, %class.A** %this.addr, align 8
  store i32 %a, i32* %a.addr, align 4
  %this1 = load %class.A*, %class.A** %this.addr, align 8
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define linkonce_odr dso_local void @_ZN1A3fooEv(%class.A* %this) unnamed_addr #3 comdat align 2 {
entry:
  %this.addr = alloca %class.A*, align 8
  store %class.A* %this, %class.A** %this.addr, align 8
  %this1 = load %class.A*, %class.A** %this.addr, align 8
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define linkonce_odr dso_local void @_ZN1B2m1Ei(%class.B* %this, i32 %a) unnamed_addr #3 comdat align 2 {
entry:
  %this.addr = alloca %class.B*, align 8
  %a.addr = alloca i32, align 4
  store %class.B* %this, %class.B** %this.addr, align 8
  store i32 %a, i32* %a.addr, align 4
  %this1 = load %class.B*, %class.B** %this.addr, align 8
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define linkonce_odr dso_local void @_ZN1B3fooEv(%class.B* %this) unnamed_addr #3 comdat align 2 {
entry:
  %this.addr = alloca %class.B*, align 8
  store %class.B* %this, %class.B** %this.addr, align 8
  %this1 = load %class.B*, %class.B** %this.addr, align 8
  ret void
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
