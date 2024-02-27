"use strict";this.default_r_zfdvltmqh=this.default_r_zfdvltmqh||{};(function(_){var window=this;
try{
_.gSb=function(a){a.focus();if(document.activeElement!==a){a.setAttribute("tabindex","-1");var b=()=>{a.removeAttribute("tabindex");a.removeEventListener("blur",b);a.removeEventListener("mousedown",b)};a.addEventListener("blur",b);a.addEventListener("mousedown",b);a.focus()}};
}catch(e){_._DumpException(e)}
try{
var fBc=function(a,b){return a.length!==b.length?!1:a.every((c,d)=>c.path===b[d].path)},gBc=function(a){const b=a.children.primary;return b?[...a.segments,...gBc(b)]:a.segments};_.hBc=function(a){(a=a.doc.getElementById("main"))&&a!==document.activeElement&&_.gSb(a)};
_.iBc=class{constructor(a,b,c){this.childrenOutletContexts=a;this.doc=b;this.router=c;a=c.events.pipe(_.Me(d=>d instanceof _.Vl||d instanceof _.Mg),_.Bf(null),_.sf(),_.Me(([d,e])=>!(d instanceof _.Vl&&e instanceof _.Vl)),_.A(([,d])=>d));b=_.He(b,"focus",{capture:!0}).pipe(_.Hf(a),_.Me(([,d])=>d instanceof _.Vl),_.A(([,d])=>d.id),_.Bf(-1));a.pipe(_.A(d=>{var e=this.router.url,f;const g=null==(f=this.childrenOutletContexts.getContext("primary"))?void 0:f.route;f=g?_.rm(this.router,["."],{relativeTo:g}):
null;return{event:d,url:e,rootOutletTree:f,activeSandboxId:this.getActiveSandboxId()}}),_.sf(),_.Me(([d])=>d.event instanceof _.Vl)).pipe(_.Hf(b),_.Me(([[d,e],f])=>{(f=d.event.id===f&&document.activeElement!==document.body||!this.shouldHandleNavigation(d,e))||(d=d.rootOutletTree,e=e.rootOutletTree,d&&e?(d=gBc(d.root),e=gBc(e.root),e=!fBc(d,e)):e=!1,f=!e);return f?!1:!0})).subscribe(()=>{_.hBc(this)},d=>{this.logError(d)})}logError(a){const b=a instanceof Error?a.message:`${a}`;a={stack:a instanceof
Error?a.stack||"":""};_.Wg().logClientError({message:b,metadata:a,eventType:"navigationFocus",eventName:"navigationFocusError",errorExperience:6})}};_.iBc=_.fj([_.VCa(1,(0,_.bl)(_.Lg)),_.WCa([_.Xl,Document,_.sm])],_.iBc);
}catch(e){_._DumpException(e)}
try{
_.Rg("pm_navigation_focus_rif");
var jBc=class extends _.iBc{shouldHandleNavigation(a,b){return!_.Nc(a.url).getPath().endsWith("rif-empty-page")&&!_.Nc(b.url).getPath().endsWith("rif-empty-page")}getActiveSandboxId(){return null}};jBc.\u0275fac=function(a){return new (a||jBc)(_.k(_.Xl),_.k(_.Lg),_.k(_.sm))};jBc.\u0275prov=_.h({token:jBc,factory:jBc.\u0275fac,providedIn:"root"});var kBc=class{};kBc.\u0275fac=function(a){return new (a||kBc)};kBc.\u0275mod=_.ud({type:kBc,id:"pm_navigation_focus_rif"});
kBc.\u0275inj=_.gd({providers:[{provide:_.Dm,useValue:{NavigationFocusRif:jBc}}]});_.If(kBc,"pm_navigation_focus_rif");
_.Sg();
}catch(e){_._DumpException(e)}
}).call(this,this.default_r_zfdvltmqh);
// Google Inc.
