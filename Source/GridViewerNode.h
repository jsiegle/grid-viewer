/*
 ------------------------------------------------------------------

 This file is part of the Open Ephys GUI
 Copyright (C) 2013 Open Ephys

 ------------------------------------------------------------------

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.

 */

#ifndef __GRIDVIEWERNODE_H__
#define __GRIDVIEWERNODE_H__

#include "ProcessorHeaders.h"


namespace GridViewer {

class ActivityView
{
public:
    /** Constructor */
	ActivityView(int numChannels, int updateInterval);

    /** Returns a pointer to the peak-to-peak values across channels*/
	const float* getPeakToPeakValues();

    /** Adds an incoming sample for a given channel */
	void addSample(float sample, int channel);

    /** Reset min/max values*/
    void reset();

private:

	Array<float, CriticalSection> minChannelValues;
	Array<float, CriticalSection> maxChannelValues;
	Array<float, CriticalSection> peakToPeakValues;

	int counter;
	int updateInterval;

};


class GridViewerNode : public GenericProcessor
{
public:

    /** Constructor */
    GridViewerNode();

    /** Destructor */
    virtual ~GridViewerNode() override;

    /** Creates the editor UI */
    AudioProcessorEditor* createEditor() override;

    /** Pushes samples to the data buffer*/
    void process(AudioBuffer<float>& buffer) override;

    /** Enables the editor */
    bool startAcquisition() override;

    /** Disables the editor*/
    bool stopAcquisition() override;

    /** Changes the selected stream */
    void setParameter(int index, float value) override;

    /** Gets the latest peak-to-peak values*/
    const float* getLatestValues() { return activityView->getPeakToPeakValues(); }

private:

    std::unique_ptr<ActivityView> activityView;

	uint16 currentStream;
    int skip = 1;
    const float targetSampleRate = 500;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GridViewerNode);
};

}

#endif /* __GRIDVIEWERNODE_H__ */
