The code distributions between View and ViewModlel.

View (View or ViewController) only displays and hides UI views, setup state of the UI view, handle animations of the UI Views.
View doesn’t interact with the Interactors, Services or App Specific logic in any way.

ViewModel - Makes decision when and what should be displayed on the View.
To do so it calls the methods of the View.
So in general ViewVodel handle current state and state changes of a View,
also responds to UI View and it’s subviews delegate methods calls (the way to handle user input).
ViewModel interacts with other parts of the app by using Interactor.

Interactor - contains business logic of the app.
It contains scenario and behavior for the particular isolated workflow.
It calls methods of services, application specific logic, responds to the application events and can call methods of other Interactors.
So if we will describe the app as a tree, the app specific logic and services are the tree trunks,
Interactors are the tree branches, ViewModels are the leaf stalks, tree leaf itself is the View.
