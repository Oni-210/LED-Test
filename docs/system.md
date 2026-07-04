# System
This system uses a system defined within the visuals.h and visual_tools.h files and the expressions folder.

## Inheritance
Visual -> Expressions -> VisualTools

The visuals.h file provides the essentials. Those are the Color class primarily used for arrays containing images. 

There are also the Enums for Expressions and TempExpressions. An expression is something that can be shown for an undefined amount of time. A TempExpression is something with a fixed length after which the system returns to the expression shown before.

But the most important thing is the Visual base class. This provides the basic system that can be extended for the specific expression. Every time a new frame should be shown, the run function is executed and returns a unique_ptr to a Color[]. This contains the next frame.


In the expressions folder, there are all the different types of expressions as children of Visual. These can be specific expressions or generalized versions that can be initialized as different expressions.

The VisualTools class finally provides a way to get the Visual from the Expression Enum. When given the Enum, it returns a smart pointer to the needed visual.

## Naming
Constant Case for constants
‘CASE_FOR_CONSTANTS’
PascalCase for classes
‘CaseForClasses’
Camel Case for Functions
‘caseForFunctions’
Snake Case for variables
‘case_for_variables’