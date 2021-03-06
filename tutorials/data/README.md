# Data sets

This section explains the different data sets that can be processed using BOSS. There are essentially three types of data files of relevance here:

* **Raw data**

  These are data files containing raw recorded data from either real measurements in BESIII or from Monte Carlo simulations.  
  Extension: `rtraw` or `raw`, see [here](https://docbes3.ihep.ac.cn/~offlinesoftware/index.php/How_to_mix_two_MC_samples) for how to convert them into each other.

* **Reconstructed data** Raw files are too large to be handled in an analysis: the recorded data first has to be converted to tracks data. The output of this reconstruction step is a DST file. Extension: `dst`.
* **Output from the initial event selection** In the analysis step, you analyse the events contained in the DST files. The output of that analysis is stored to a `TTree` in a ROOT file. Extension: `root`

## Locations on the IHEP Server

Inventories of the latest file locations are found on the Offline Software pages \(requires login\):

* [Raw data](https://docbes3.ihep.ac.cn/~offlinesoftware/index.php/Raw_Data)
* [Reconstructed data](https://docbes3.ihep.ac.cn/~offlinesoftware/index.php/Production)

In general, all data files are located on the BESIII file system \(`besfs`\) folders on the [IHEP Server](../getting-started/server.md). There are a few different folders, because the files have been distributed to different servers.

* **`besfs`**: contains user files only
* **`besfs2`**: a symbolic link that points to `/besfs3/offline/data/besfs2`. Contains inclusive Monte Carlo samples.
* **`besfs3`**: file system that contains files of the runs before 2018
* **`bes3fs`**: a newer file system that contains for instance 2018 data

Within these folders, the data files are located under `offline/data` \(e.g. `/besfs3/offline/data`\) and then the BOSS version with which these files have been created.

{% hint style="warning" %}
Make sure you do not confuse the numbers when navigating these paths.
{% endhint %}

