# Assignment 02 — UE5 Calculator + Unit Converter

**Course:** Games 6900-008: C++ in Unreal Engine  
**Repo to Submit:** [assignment02](https://eae-git.eng.utah.edu/6900-008_cppunrealengine/assignment02)  
**Difficulty:** 5 / 10  

---

## 📖 Overview
In this assignment, you will extend the **UnrealOOP_Calculator** project to support **unit conversion (Miles ⇄ Feet ⇄ Centimeters)**.  

You will:  
- Use the supplied scaffold files (`UnitConverterAPI_HEADER.txt` / `UnitConverterAPI_SOURCE.txt`) to implement the new C++ class `UnitConverterAPI`.  
- Complete the `#TODO`s in C++ for conversion factors and math.  
- Add Blueprint logic in the provided `WBP_Calculator` so the **Convert button** works.  
- Place your DLL from Assignment 01 so calculator operations continue to work.  
- Submit your work on your own branch in GitLab.  

---

## 📂 Files & Project Structure
The assignment materials include two directories:  

### 1. `UUnitConverterAPI/`  
- `UnitConverterAPI_HEADER.txt` (scaffold for `.h`)  
- `UnitConverterAPI_SOURCE.txt` (scaffold for `.cpp`)  

> Copy these into the generated `.h/.cpp` files when you create the class with the UE C++ Class Wizard.  

### 2. `CalculatorUEProject/`  
- `Config/`  
- `Content/`  
- `Source/`  
- `UnrealOOP_Calculator.uproject`  

This is the full Unreal Engine project. The UI (`WBP_Calculator`) is already built with variables created for you.  

---

## 🛠 Step 1 — Create the C++ Class
1. Open `UnrealOOP_Calculator.uproject` in UE 5.6.  
2. Go to **Tools → New C++ Class…**.  
3. Choose **Blueprint Function Library** → **Next**.  
4. Name it: `UnitConverterAPI` (creates `UnitConverterAPI`).  
5. Module: `UnrealOOP_Calculator`.  
6. **Create Class** (opens Visual Studio).  

Replace the generated files:  
- Paste `UnitConverterAPI_HEADER.txt` → `UnitConverterAPI.h`  
- Paste `UnitConverterAPI_SOURCE.txt` → `UnitConverterAPI.cpp`  

---

## 🛠 Step 2 — Complete the C++ TODOs
### `UnitFactorToCm()`  
- Miles → 160934.4  
- Feet → 30.48  
- Centimeters → 1.0  
- Return `false` if unknown  

### `ConvertUnits()`  
- Use `UnitFactorToCm()` for From and To.  
- If either fails, return NaN:  
```cpp
  return std::numeric_limits<double>::quiet_NaN();
```

* Else:

  * `inCm = Value * FromFactor`
  * `result = inCm / ToFactor`
  * Return result

### `IndexToUnit()`

* 0 → Miles
* 1 → Feet
* 2 → Centimeters

### `ConvertUnitsByIndex()` (**Required**)

* Use `IndexToUnit()` for both indices.
* If either fails, return NaN.
* Otherwise call `ConvertUnits(Value, FromUnit, ToUnit)`.

---

## 🛠 Step 3 — Blueprint Wiring (`WBP_Calculator`)

All variables and dropdown setup are already done for you.
👉 You only need to complete the **Convert Button → OnClicked** logic.

### Convert Button Logic

1. In the Designer, select **Btn\_Convert** → **Details → Events → + OnClicked**.

   * This creates `Event OnClicked (Btn_Convert)` in the Graph.

2. **Read the numeric input**

   * Get `Txt_Value` → `GetText` → `Conv_TextToString` → `String To Float/Double`.
   * This gives you the input **Value**.

3. **Find From/To indices**

   * Use the provided nodes: `Element01 (Miles)`, `Element02 (Feet)`, `Element03 (Centimeters)`.
   * Connect them into a **Make Array** node.
   * From this array:

     * `Find Item (FromUnit)` → **FromIndex**
     * `Find Item (ToUnit)` → **ToIndex**
   * Add a **Branch**: if either index = -1 → set `Txt_Converted` = `"Converted: NaN"` and return.

4. **Call your C++ function**

   * Search for **“Convert Units (By Index)”** node.
   * Wire: `Value`, `FromIndex`, `ToIndex`.
   * Output: **ReturnValue** (double/float).

5. **Display the result**

   * Convert ReturnValue → Text (`Conv_FloatToText` / `Conv_DoubleToText`).
   * Connect it into the provided **Append node** (already scaffolded).
   * The Append node formats `"Converted: <result>"`.
   * Connect the Append output into the provided **SetText (Txt\_Converted)** node.

---

## 🛠 Step 4 — DLL Placement

Copy your DLL from Assignment 01 into:

```
UnrealOOP_Calculator/Binaries/Win64/ArithmeticAPI.dll
```

---

## 🧪 Step 5 — Test Cases

Check these cases inside PIE (Play-In-Editor):

1. `1 Mile → Feet` = **5280**
2. `1 Foot → Centimeters` = **30.48**
3. `1 Mile → Centimeters` = **160,934.4**
4. `123.45 Centimeters → Feet` ≈ **4.05**
5. `7.5 Feet → Feet` = **7.5**

---

## 📦 Step 6 — Submission Instructions

1. Clone the repo:
   [assignment02](https://eae-git.eng.utah.edu/6900-008_cppunrealengine/assignment02)

2. Create your own branch, named:

   ```
   <YourName-unid>
   ```

   Example: `JaneDoe-u1234567`

3. Commit only these **top-level items** from `CalculatorUEProject/`:

   * `Config/`
   * `Content/`
   * `Source/`
   * `UnrealOOP_Calculator.uproject`

4. **Do not commit**: `Binaries/`, `Intermediate/`, `Saved/`, `DerivedDataCache/`, `.vs/`, `.sln`, `.vcxproj`.

   * Use the provided `.gitignore` in the repo to help you.

5. Push your branch and confirm it appears on GitLab.

---

## ⚠️ Tips

* ComboBox order **must** be Miles (0), Feet (1), Centimeters (2).
* If “Convert Units (By Index)” doesn’t show: build in Visual Studio first, then click **Compile** in UE.