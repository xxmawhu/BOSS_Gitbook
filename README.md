# The BOSS GitBook

{% hint style="warning" %}
Feedback on these pages is very welcome! See [About](appendices/about.md) for contact details.
{% endhint %}

This GitBook describes the use of the BESIII Offline Software System \(BOSS\). These pages started as a collection of notes, but now aim to serve several purposes:

* Provide accessible and up-to-date **tutorials** on working with BOSS. These pages written as step-by-step guides and are particularly aimed at beginners, but also provide background information of what the software is doing.
* Serve as an **inventory of packages** and libraries often used within BOSS. Ideally, this should allow analysers to navigate through the tools that are already available.
* Serve as a platform where analysers can **easily and continuously update** their documentation.
* Maintain an **updated list of references** to must-read web pages or literature on BESIII.

What goes for all of the above is that, whatever your background or level, _**your feedback is vital**_. These tutorial pages are quite new and need testing and improvement. More importantly, the more people contribute, the more these pages can become a reference source.

So if you read this and like the idea, do have a look at the [contributing page](appendices/contributing.md)!  
Contributions from all levels is highly appreciated.

{% hint style="info" %}
If you do not have an IHEP networking account, it is better to check out the official [Offline Software page](http://english.ihep.cas.cn/bes/doc/2247.html) of BESIII. For this, you in turn need to be a BESIII member and have an SSO account, which can be done [here](http://afsapply.ihep.ac.cn/cchelp/en/accounts/#21-user-account-application).

BOSS can only be of use if you are a member of the BESIII collaboration and if you have access to the software of this collaboration. You can also have a look at the links in the section [Further reading](appendices/references.md).
{% endhint %}

## Contents of the tutorial pages

This [GitBook](https://besiii.gitbook.io/boss) provides tutorials for using the BOSS Analysis Framework used in the BESIII collaboration. Currently, the pages have been written from the perspective of \(light\) hadron spectroscopy, but the tutorials can be useful for other forms of analysis as well.

Here are shortcuts that you might want to take:

1. [**Getting started with BOSS**](tutorials/getting-started/) ****If you are not familiar with BOSS, it is best to start with this part of the tutorial. It will help you set up the BOSS environment in your account on the IHEP server \('install BOSS'\), explain you some basics of the package structure on which BOSS is built, and guide you through the process of submitting jobs.
2. [**Major BOSS packages**](packages/intro.md) ****Here, you will find descriptions of some of the important BOSS packages used in initial event selection, most notably, the `RhopiAlg` package. This section is to serve as an inventory of BOSS packages.
3. \*\*\*\*[**Physics at BESIII**](physics/intro/)  
   An inventory of important physics principles behind of data analysis at BESIII.

   _\(These pages have not yet been written.\)_

4. [**Tips, Tricks, and Troubleshooting**](appendices/tips/) ****These pages are used to collect problems that are frequently encountered when working with BOSS. As such, these notes are useful no matter your level. _New suggestions are most welcome!_

## A note on the _BOSS Afterburner_

Initially, these pages were part of the [_BOSS Afterburner_ repository](https://github.com/redeboer/BOSS_Afterburner). This repository has been split up into the pages that you are currently looking at and separates repositories that serves as extensions to BOSS, which aims providing tools to standardise analysis procedures at BESIII.

* \*\*\*\*[**BOSS Starter Kit**](https://github.com/redeboer/BOSS_StarterKit), containing the following submodules:
  * [Tutorials](https://github.com/redeboer/BOSS_Tutorials)
  * [Job Submitter](https://github.com/redeboer/BOSS_JobSubmitter)
  * [IniSelect](https://github.com/redeboer/BOSS_IniSelect)
* \*\*\*\*[**BOSS Afterburner**](https://github.com/redeboer/BOSS_Afterburner)\*\*\*\*

