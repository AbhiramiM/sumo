/****************************************************************************/
/// @file    GNESelectorFrame.h
/// @author  Jakob Erdmann
/// @date    Mar 2011
/// @version $Id: GNESelectorFrame.h 20785 2016-05-24 10:51:45Z palcraft $
///
// The Widget for modifying selections of network-elements
// (some elements adapted from GUIDialog_GLChosenEditor)
/****************************************************************************/
// SUMO, Simulation of Urban MObility; see http://sumo.dlr.de/
// Copyright (C) 2001-2016 DLR (http://www.dlr.de/) and contributors
/****************************************************************************/
//
//   This file is part of SUMO.
//   SUMO is free software: you can redistribute it and/or modify
//   it under the terms of the GNU General Public License as published by
//   the Free Software Foundation, either version 3 of the License, or
//   (at your option) any later version.
//
/****************************************************************************/
#ifndef GNESelectorFrame_h
#define GNESelectorFrame_h

// ===========================================================================
// included modules
// ===========================================================================
#ifdef _MSC_VER
#include <windows_config.h>
#else
#include <config.h>
#endif

#include "GNEFrame.h"

// ===========================================================================
// class declarations
// ===========================================================================
class GNEAttributeCarrier;

// ===========================================================================
// class definitions
// ===========================================================================
/**
 * @class GNESelectorFrame
 * The Widget for modifying selections of network-elements
 */
class GNESelectorFrame : public GNEFrame, public GUISelectedStorage::UpdateTarget {
    // FOX-declarations
    FXDECLARE(GNESelectorFrame)

public:

    enum SetOperation {
        SET_ADD      = 1,
        SET_SUB      = 2,
        SET_RESTRICT = 3,
        SET_REPLACE  = 4,
        SET_DEFAULT  = 5  // use mySetOperation instead of override
    };

    /**@brief Constructor
     * @param[in] parent The parent window
     */
    GNESelectorFrame(FXComposite* parent, GNEViewNet* viewNet, GNEUndoList* undoList);

    /// @brief Destructor
    ~GNESelectorFrame();

    /// @brief get header font
    FXFont* getHeaderFont() const;

    /// @name FOX-callbacks
    /// @{
    /**@brief Called when the user presses the Load-button
     *
     * Opens a file dialog and forces the parent to load the list of selected
     *  objects when a file was chosen. Rebuilds the list, then, and redraws
     *  itself.
     */
    long onCmdLoad(FXObject*, FXSelector, void*);

    /**@brief Called when the user presses the Save-button
     *
     * Opens a file dialog and forces the selection container to save the list
     *  of selected objects when a file was chosen.
     *
     * If the saveing failed, a message window is shown.
     */
    long onCmdSave(FXObject*, FXSelector, void*);

    /**@brief Called when the user presses the Clear-button
     *
     * Clear the internal list and calls GUISelectedStorage::clear.
     * Repaints itself
     */
    long onCmdClear(FXObject*, FXSelector, void*);

    /**@brief Called when the user presses the Invert-button
     * invert the selection
     * Repaints itself
     */
    long onCmdInvert(FXObject*, FXSelector, void*);

    /**@brief Called when the user selectes a tag in the match box
     * updates the attr listbox
     * Repaints itself
     */
    long onCmdSelMBTag(FXObject*, FXSelector, void*);

    /**@brief Called when the user enters a new selection expression
     * validates expression and modifies current selection
     */
    long onCmdSelMBString(FXObject*, FXSelector, void*);

    /**@brief Called when the user clicks the help button
     * pop up help window
     */
    long onCmdHelp(FXObject*, FXSelector, void*);

    /**@brief Called when the user changes visual scaling
     */
    long onCmdScaleSelection(FXObject*, FXSelector, void*);

    /// @}

    void show();

    void hide();

    /* apply list of ids to the current selection according to SetOperation,
     * if setop==SET_DEFAULT than the currently set mode (mySetOperation) is used */
    void handleIDs(std::vector<GUIGlID> ids, bool selectEdges, SetOperation setop = SET_DEFAULT);

    /* @brief called if currently registered for updates for changes of global selection */
    void selectionUpdated();

protected:
    /// @brief FOX needs this
    GNESelectorFrame() {}

private:
    /// @brief the panel to hold all member widgets
    FXVerticalFrame* myContentFrame;

    /// @brief Font for the widget
    FXFont* myHeaderFont;

    /// @brief the label for selection statistics
    FXLabel* myStats;

    /// @brief how to modify selection
    FXuint mySetOperation;
    FXDataTarget mySetOperationTarget;

    /// @brief state variables for the match box
    FXListBox* myMatchTagBox;
    FXListBox* myMatchAttrBox;
    FXTextField* myMatchString;

    FXRealSpinDial* mySelectionScaling;

private:

    std::string getStats() const;

    /**@brief return  objects of the given type with matching attrs
     * @param[in] compOp One of {<,>,=} for matching against val or '@' for
     *                   matching against expr
     */
    std::vector<GUIGlID> getMatches(
        SumoXMLTag tag, SumoXMLAttr attr, char compOp, SUMOReal val, const std::string& expr);

    // the string that should be matched against if attr 'allowed' or 'disalloed' are set to "all"
    const std::string ALL_VCLASS_NAMES_MATCH_STRING;
};


#endif

/****************************************************************************/

