RandomNumberGUIService
======================

JUCE GUI project for M+M Random Number Service

Currently tested with Windows VS only. For xcode projects, the additional directories for MPlusM, yarp, and ACE headers and library locations need to be set.

After auto generation of the VS project, it is necessary to manually change the dependency to ACE.lib to ACEd.lib (due to the way we're compiling ACE and how JUCE expects debug/release libs to have the same name but possibly in different folders).
