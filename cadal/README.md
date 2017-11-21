# CADAL

A presents ideas sharing tool.

It's this time of the year again when family members/friends/coworkers/... are
going to exchange presents. But finding THE idea, the perfect present, is as
usual a struggle.

What if you could exchange with others without the recipient
knowing about it?

What if the recipient could help by listing a few ideas of their own, but not
see comments from the others?


## The idea

Mom, Dad, Daughter and Son are all wanting to offer presents to each other for
christmas.

Mom logs in, and can see that Dad added a present idea for Son (a new guitar),
and Daughter commented that she knew Son wanted a specific brand/model.

Mom can chip in and say that she knows where to buy it, and will take care of
it.

She doesn't know that Dad, Daughter and Son are discussing an idea that Son
added for her (singing lessons).

Mom also added a couple of ideas of her own for herself (a new scarf, some
makeup), but she doesn't know if Dad, Daughter and Son commented on them, of if
they're willing to buy those.

Before logging off, she adds a present idea for Daughter: she selects the "add
new idea", selects "Daughter" from the dropdown list, enters a title (bicycle)
and a short description (she loves her current bike, but it's becomming way too
small for her, let's get her this new model, what do you think?).

## Current status

This is an experiment. The initial implementation of this idea was done in PHP
in half a day on the 1st of December 2008, storing the data in a mysql
database.

This repository is an attempt at rewriting it in
[ReasonReact](https://reasonml.github.io/reason-react/docs/en/installation.html),
using [reason-scripts](https://github.com/reasonml-community/reason-scripts),
and storing the data in [Kinto](https://kinto.readthedocs.io/en/stable/) to
make use of its permissions system, which should ease the authorizations
management (who can see what).


## Kinto data organisation

- Bucket: the group of people exchanging ideas. In our example, Mom, Dad,
  Daughter and Son.
    - Users collection
        - User records: one per user (four in our example)
    - Event collection: one collection per event (eg christmas-2017,
      mom-birthday, dad-retirement...)
        - Idea records: one per idea
    - Comments collection: one per idea (eg comments-{id_record})
        - Comment records: one record per comment


### Setting up a new "group"

As a kinto admin:
- Create a new bucket (eg MomDadDaughterSon)
- Create a new group (eg MomDadDaughterSon)
- Add each user: choose a login/password and login using the
  [kinto-admin](https://kinto.agopian.info/v1/admin/), then copy/paste the user
  ID which will be something like `basicauth:.....`
- Change the bucket permissions for the group: allowed to write and
  collection:create
